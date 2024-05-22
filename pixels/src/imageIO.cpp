/*
* image input/output supporting exr png tga hdr bmp image file formats (rgb or rgba only)
* converted to/from float data, when necessary...
* using tinyexr and stb
* 
* https://github.com/tuttleofx/TuttleOFX/blob/36fc4cae15092a84ea8c29b9c6658c7cabfadb6e/plugins/image/io/Exr/src/reader/EXRReaderProcess.tcc
* https://stackoverflow.com/questions/67777769/c-opengl-stb-image-h-errors
* https://stackoverflow.com/questions/59774647/loading-image-with-stb-image-library-as-float-outputs-wrong-values
*/

// header only includes must be in cpp files..
#define TINYEXR_IMPLEMENTATION
#include "tinyexr.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "imageIO.h"

float* loadImageSTB(const std::string filepath, int& width, int& height, int& channels) {
    std::cout << "loadImageSTB file " << filepath << std::endl;
    stbi_ldr_to_hdr_gamma(1.0f);
    return stbi_loadf(filepath.c_str(), &width, &height, &channels, STBI_rgb_alpha);
}

float* loadImageEXR(const std::string filepath, int& width, int& height, int& channels) {
    float* pixels;
    const char* input = filepath.c_str();
    EXRVersion exr_version;

    int ret = ParseEXRVersionFromFile(&exr_version, input);
    if (ret != 0) {
        fprintf(stderr, "Invalid EXR file: %s\n", input);
        return NULL;
    }

    if (exr_version.multipart) {
        // must be multipart flag is false.
        fprintf(stderr, "Must be a singlepart image: %s\n", input);
        return NULL;
    }

    EXRHeader exr_header;
    InitEXRHeader(&exr_header);

    const char* err = NULL; // or `nullptr` in C++11 or later.
    ret = ParseEXRHeaderFromFile(&exr_header, &exr_version, input, &err);
    if (ret != 0) {
        fprintf(stderr, "Parse EXR err: %s\n", err);
        FreeEXRErrorMessage(err); // free's buffer for an error message
        //return false;
        return NULL;
    }

    std::cout << "loadImageEXR file " << filepath << std::endl;
    std::cout << "channels " << exr_header.num_channels << std::endl;

    // Read HALF channel as FLOAT.
    for (int i = 0; i < exr_header.num_channels; i++) {
        if (exr_header.pixel_types[i] == TINYEXR_PIXELTYPE_HALF) {
            exr_header.requested_pixel_types[i] = TINYEXR_PIXELTYPE_FLOAT;
        }
    }

    EXRImage exr_image;
    InitEXRImage(&exr_image);

    ret = LoadEXRImageFromFile(&exr_image, &exr_header, input, &err);
    if (ret != 0) {
        std::cerr << "imageLoader error: " << err << std::endl;
        FreeEXRHeader(&exr_header);
        FreeEXRErrorMessage(err); // free's buffer for an error message
        return NULL;
    }

    // Copy image data
    std::cout << "imageLoader dims: " << exr_image.width << ", " << exr_image.height << ", channels: " << exr_image.num_channels << std::endl;
    // RGBA
    int idxR = -1;
    int idxG = -1;
    int idxB = -1;
    int idxA = -1;
    for (int c = 0; c < exr_header.num_channels; c++) {
        if (strcmp(exr_header.channels[c].name, "R") == 0) {
            idxR = c;
        }
        else if (strcmp(exr_header.channels[c].name, "G") == 0) {
            idxG = c;
        }
        else if (strcmp(exr_header.channels[c].name, "B") == 0) {
            idxB = c;
        }
        else if (strcmp(exr_header.channels[c].name, "A") == 0) {
            idxA = c;
        }
    }

    if (exr_header.num_channels == 1) {
        // Grayscale channel only.
        pixels = reinterpret_cast<float*>(malloc(sizeof(float) * static_cast<size_t>(exr_image.width) * static_cast<size_t>(exr_image.height)));
        if (exr_header.tiled) {
            for (int it = 0; it < exr_image.num_tiles; it++) {
                for (int j = 0; j < exr_header.tile_size_y; j++) {
                    for (int i = 0; i < exr_header.tile_size_x; i++) {
                        const int ii = exr_image.tiles[it].offset_x * exr_header.tile_size_x + i;
                        const int jj = exr_image.tiles[it].offset_y * exr_header.tile_size_y + j;
                        const int idx = ii + jj * exr_image.width;
                        // out of region check.
                        if (ii >= exr_image.width) {
                            continue;
                        }
                        if (jj >= exr_image.height) {
                            continue;
                        }
                        const int srcIdx = i + j * exr_header.tile_size_x;
                        unsigned char** src = exr_image.tiles[it].images;
                        (pixels)[idx + 0] = reinterpret_cast<float**>(src)[0][srcIdx];
                    }
                }
            }
        }
        else {
            for (int i = 0; i < exr_image.width * exr_image.height; i++) {
                const float val = reinterpret_cast<float**>(exr_image.images)[0][i];
                pixels[i] = val;
            }
        }
    }
    else if (exr_header.num_channels == 3) {
        // RGB
        if (idxR == -1) {
            tinyexr::SetErrorMessage("R channel not found", &err);

            // @todo { free exr_image }
            FreeEXRHeader(&exr_header);
            //return TINYEXR_ERROR_INVALID_DATA;
            return NULL;
        }
        if (idxG == -1) {
            tinyexr::SetErrorMessage("G channel not found", &err);
            // @todo { free exr_image }
            FreeEXRHeader(&exr_header);
            //return TINYEXR_ERROR_INVALID_DATA;
            return NULL;
        }
        if (idxB == -1) {
            tinyexr::SetErrorMessage("B channel not found", &err);
            // @todo { free exr_image }
            FreeEXRHeader(&exr_header);
            //return TINYEXR_ERROR_INVALID_DATA;
            return NULL;
        }
        pixels = reinterpret_cast<float*>(malloc(3 * sizeof(float) * static_cast<size_t>(exr_image.width) * static_cast<size_t>(exr_image.height)));
        if (exr_header.tiled) {
            for (int it = 0; it < exr_image.num_tiles; it++) {
                for (int j = 0; j < exr_header.tile_size_y; j++) {
                    for (int i = 0; i < exr_header.tile_size_x; i++) {
                        const int ii =
                            exr_image.tiles[it].offset_x * exr_header.tile_size_x + i;
                        const int jj =
                            exr_image.tiles[it].offset_y * exr_header.tile_size_y + j;
                        const int idx = ii + jj * exr_image.width;

                        // out of region check.
                        if (ii >= exr_image.width) {
                            continue;
                        }
                        if (jj >= exr_image.height) {
                            continue;
                        }
                        const int srcIdx = i + j * exr_header.tile_size_x;
                        unsigned char** src = exr_image.tiles[it].images;
                        (pixels)[3 * idx + 0] = reinterpret_cast<float**>(src)[idxR][srcIdx];
                        (pixels)[3 * idx + 1] = reinterpret_cast<float**>(src)[idxG][srcIdx];
                        (pixels)[3 * idx + 2] = reinterpret_cast<float**>(src)[idxB][srcIdx];

                    }
                }
            }
        }
        else {
            for (int i = 0; i < exr_image.width * exr_image.height; i++) {
                pixels[3 * i + 0] = reinterpret_cast<float**>(exr_image.images)[idxR][i];
                pixels[3 * i + 1] = reinterpret_cast<float**>(exr_image.images)[idxG][i];
                pixels[3 * i + 2] = reinterpret_cast<float**>(exr_image.images)[idxB][i];
            }
        }

    }
    else {
        // Assume RGBA
        if (idxR == -1) {
            tinyexr::SetErrorMessage("R channel not found", &err);

            // @todo { free exr_image }
            FreeEXRHeader(&exr_header);
            //return TINYEXR_ERROR_INVALID_DATA;
            return NULL;
        }
        if (idxG == -1) {
            tinyexr::SetErrorMessage("G channel not found", &err);
            // @todo { free exr_image }
            FreeEXRHeader(&exr_header);
            //return TINYEXR_ERROR_INVALID_DATA;
            return NULL;
        }
        if (idxB == -1) {
            tinyexr::SetErrorMessage("B channel not found", &err);
            // @todo { free exr_image }
            FreeEXRHeader(&exr_header);
            //return TINYEXR_ERROR_INVALID_DATA;
            return NULL;
        }
        pixels = reinterpret_cast<float*>(malloc(4 * sizeof(float) * static_cast<size_t>(exr_image.width) * static_cast<size_t>(exr_image.height)));
        if (exr_header.tiled) {
            for (int it = 0; it < exr_image.num_tiles; it++) {
                for (int j = 0; j < exr_header.tile_size_y; j++) {
                    for (int i = 0; i < exr_header.tile_size_x; i++) {
                        const int ii =
                            exr_image.tiles[it].offset_x * exr_header.tile_size_x + i;
                        const int jj =
                            exr_image.tiles[it].offset_y * exr_header.tile_size_y + j;
                        const int idx = ii + jj * exr_image.width;

                        // out of region check.
                        if (ii >= exr_image.width) {
                            continue;
                        }
                        if (jj >= exr_image.height) {
                            continue;
                        }
                        const int srcIdx = i + j * exr_header.tile_size_x;
                        unsigned char** src = exr_image.tiles[it].images;
                        (pixels)[4 * idx + 0] =
                            reinterpret_cast<float**>(src)[idxR][srcIdx];
                        (pixels)[4 * idx + 1] =
                            reinterpret_cast<float**>(src)[idxG][srcIdx];
                        (pixels)[4 * idx + 2] =
                            reinterpret_cast<float**>(src)[idxB][srcIdx];
                        if (idxA != -1) {
                            (pixels)[4 * idx + 3] =
                                reinterpret_cast<float**>(src)[idxA][srcIdx];
                        }
                        else {
                            (pixels)[4 * idx + 3] = 1.0;
                        }
                    }
                }
            }
        }
        else {
            for (int i = 0; i < exr_image.width * exr_image.height; i++) {
                pixels[4 * i + 0] =
                    reinterpret_cast<float**>(exr_image.images)[idxR][i];
                pixels[4 * i + 1] =
                    reinterpret_cast<float**>(exr_image.images)[idxG][i];
                pixels[4 * i + 2] =
                    reinterpret_cast<float**>(exr_image.images)[idxB][i];
                if (idxA != -1) {
                    pixels[4 * i + 3] =
                        reinterpret_cast<float**>(exr_image.images)[idxA][i];
                }
                else {
                    pixels[4 * i + 3] = 1.0;
                }
            }
        }
    }
    width = exr_image.width;
    height = exr_image.height;
    channels = exr_image.num_channels;

    // Free image data
    FreeEXRImage(&exr_image);
    FreeEXRHeader(&exr_header);
    return pixels;
}

bool saveImageEXR_rgb(const char* outfilename, int width, int height, const float* rgb) {
    std::cout << "saveImageEXR_rgb file " << outfilename << std::endl;
    EXRHeader header;
    InitEXRHeader(&header);
    EXRImage image;
    InitEXRImage(&image);
    image.num_channels = 3;
    std::vector<float> images[3];
    images[0].resize(width * height);
    images[1].resize(width * height);
    images[2].resize(width * height);

    // Split RGBRGBRGB... into R, G and B layer
    for (int i = 0; i < width * height; i++) {
        images[0][i] = rgb[3 * i + 0];
        images[1][i] = rgb[3 * i + 1];
        images[2][i] = rgb[3 * i + 2];
    }
    float* image_ptr[3];
    image_ptr[0] = &(images[2].at(0)); // B
    image_ptr[1] = &(images[1].at(0)); // G
    image_ptr[2] = &(images[0].at(0)); // R
    image.images = (unsigned char**)image_ptr;
    image.width = width;
    image.height = height;
    header.num_channels = 3;
    header.channels = (EXRChannelInfo*)malloc(sizeof(EXRChannelInfo) * header.num_channels);

    // Must be (A)BGR order, since most of EXR viewers expect this channel order.
    strncpy(header.channels[0].name, "B", 255); header.channels[0].name[strlen("B")] = '\0';
    strncpy(header.channels[1].name, "G", 255); header.channels[1].name[strlen("G")] = '\0';
    strncpy(header.channels[2].name, "R", 255); header.channels[2].name[strlen("R")] = '\0';
    header.pixel_types = (int*)malloc(sizeof(int) * header.num_channels);
    header.requested_pixel_types = (int*)malloc(sizeof(int) * header.num_channels);
    for (int i = 0; i < header.num_channels; i++) {
        header.pixel_types[i] = TINYEXR_PIXELTYPE_FLOAT; // pixel type of input image
        header.requested_pixel_types[i] = TINYEXR_PIXELTYPE_HALF; // pixel type of output image to be stored in .EXR
    }
    const char* err = NULL; // or nullptr in C++11 or later.
    int ret = SaveEXRImageToFile(&image, &header, outfilename, &err);
    if (ret != TINYEXR_SUCCESS) {
        std::cerr << "saveImageEXR_rgb error: " << ret;
        FreeEXRErrorMessage(err); // free's buffer for an error message
        return false;
    }
    std::cout << "Saved rgb exr file " << outfilename << std::endl;
    free(header.channels);
    free(header.pixel_types);
    free(header.requested_pixel_types);
    return true;
}

bool saveImageEXR_rgba(const char* outfilename, int width, int height, const float* rgba) {
    std::cout << "saveImageEXR_rgba file " << outfilename << std::endl;
    EXRHeader header;
    InitEXRHeader(&header);
    EXRImage image;
    InitEXRImage(&image);
    image.num_channels = 4;
    std::vector<float> images[4];
    images[0].resize(width * height);
    images[1].resize(width * height);
    images[2].resize(width * height);
    images[3].resize(width * height);

    // Split RGBRGBRGB... into R, G and B layer
    for (int i = 0; i < width * height; i++) {
        images[0][i] = rgba[image.num_channels * i + 0];
        images[1][i] = rgba[image.num_channels * i + 1];
        images[2][i] = rgba[image.num_channels * i + 2];
        images[3][i] = rgba[image.num_channels * i + 3];
    }
    float* image_ptr[4];
    image_ptr[0] = &(images[3].at(0)); // A
    image_ptr[1] = &(images[2].at(0)); // B
    image_ptr[2] = &(images[1].at(0)); // G
    image_ptr[3] = &(images[0].at(0)); // R
    image.images = (unsigned char**)image_ptr;
    image.width = width;
    image.height = height;
    header.num_channels = 4;
    header.channels = (EXRChannelInfo*)malloc(sizeof(EXRChannelInfo) * header.num_channels);

    // Must be (A)BGR order, since most of EXR viewers expect this channel order.
    strncpy(header.channels[0].name, "A", 255); header.channels[0].name[strlen("A")] = '\0';
    strncpy(header.channels[1].name, "B", 255); header.channels[1].name[strlen("B")] = '\0';
    strncpy(header.channels[2].name, "G", 255); header.channels[2].name[strlen("G")] = '\0';
    strncpy(header.channels[3].name, "R", 255); header.channels[3].name[strlen("R")] = '\0';
    header.pixel_types = (int*)malloc(sizeof(int) * header.num_channels);
    header.requested_pixel_types = (int*)malloc(sizeof(int) * header.num_channels);
    for (int i = 0; i < header.num_channels; i++) {
        header.pixel_types[i] = TINYEXR_PIXELTYPE_FLOAT; // pixel type of input image
        header.requested_pixel_types[i] = TINYEXR_PIXELTYPE_HALF; // pixel type of output image to be stored in .EXR
    }
    const char* err = NULL; // or nullptr in C++11 or later.
    int ret = SaveEXRImageToFile(&image, &header, outfilename, &err);
    if (ret != TINYEXR_SUCCESS) {
        std::cerr << "saveImageEXR_rgba error: " << ret;
        FreeEXRErrorMessage(err); // free's buffer for an error message
        return false;
    }
    std::cout << "Saved rgba exr file " << outfilename << std::endl;
    free(header.channels);
    free(header.pixel_types);
    free(header.requested_pixel_types);
    return true;
}

namespace ImageIO {

    float* loadImage(const std::string filepath, int& width, int& height, int& channels) {
        if (filepath.find(".exr") != std::string::npos) {
            return loadImageEXR(filepath, width, height, channels);
        }
        else if (filepath.find(".png") != std::string::npos) {
            return loadImageSTB(filepath, width, height, channels);
        }
        else {
            std::cerr << "unsupported format: " << filepath;
            return nullptr;
        }
        return nullptr;
    }


    bool saveImage(const std::string filepath, int& width, int& height, int& channels, const float* data) {
        bool result = false;
        if (filepath.find(".exr") != std::string::npos) {
            if (channels == 3)
                result = saveImageEXR_rgb(filepath.c_str(), width, height, data);
            else if (channels == 4)
                result = saveImageEXR_rgba(filepath.c_str(), width, height, data);
            else {
                std::cerr << "unsupported exr number of channels (only rgb & rgba are supported): " << channels << " file: " << filepath;
                result = false;
            }
        }
        else if (filepath.find(".hdr") != std::string::npos) {
            std::cout << "stbi_write_hdr file " << filepath << std::endl;
            result = 1 == stbi_write_hdr(filepath.c_str(), width, height, channels, data);
        }
        else {
            uint8_t* pixels = new uint8_t[width * height * channels];
            int index = 0;
            for (int j = height - 1; j >= 0; --j)
            {
                for (int i = 0; i < width; ++i)
                {
                    for (int c = 0; c < channels; c++) {
                        pixels[index] = int(255 * data[index++]);
                    }
                }
            }
            if (filepath.find(".png") != std::string::npos) {
                std::cout << "stbi_write_png file " << filepath << std::endl;
                result = 1 == stbi_write_png(filepath.c_str(), width, height, channels, pixels, width * channels);
            }
            else if (filepath.find(".bmp") != std::string::npos) {
                std::cout << "stbi_write_bmp file " << filepath << std::endl;
                result = 1 == stbi_write_bmp(filepath.c_str(), width, height, channels, pixels);
            }
            else if (filepath.find(".tga") != std::string::npos) {
                std::cout << "stbi_write_tga file " << filepath << std::endl;
                result = 1 == stbi_write_tga(filepath.c_str(), width, height, channels, pixels);
            }
            else {
                std::cerr << "unsupported format: " << filepath;
                result = false;
            }
            delete[] pixels;
        }
        return result;
    }
}
