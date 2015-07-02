#include "ofPixelsBitmapSource.h"

namespace zxing {

ofPixelsBitmapSource::ofPixelsBitmapSource(ofPixels& pixels) : LuminanceSource(pixels.getWidth(), pixels.getHeight()), image_(pixels) {
  width = pixels.getWidth();
  height = pixels.getHeight();
	pixel_cache = pixels.getPixels();
}

ofPixelsBitmapSource::~ofPixelsBitmapSource() {

}

int ofPixelsBitmapSource::getWidth() const {
  return width;
}

int ofPixelsBitmapSource::getHeight() const {
  return height;
}

ArrayRef<char> ofPixelsBitmapSource::getRow(int y, ArrayRef<char> row) const {
  if (!row) {
    row = new Array<char>(width);
  }
  for (int x = 0; x < width; x++) {
    const unsigned char* p = &pixel_cache[3 * (y * width + x)];
    row[x] = (unsigned char)((
				306 * (int)(*p++) +
				601 * (int)(*p++) +
				117 * (int)(*p++) + 0x200) >> 10);
  }
  return row;

}

ArrayRef<char> ofPixelsBitmapSource::getMatrix() const {
  int width = getWidth();
  int height =  getHeight();
  ArrayRef<char> matrix = new Array<char>(width*height);
  int idx = 0;
  const unsigned char* p = pixel_cache;
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
			matrix[idx] = (unsigned char)((
				306 * (int)(*p++) +
				601 * (int)(*p++) +
				117 * (int)(*p++) + 0x200) >> 10);
      idx++;
    }
  }
  return matrix;
}

bool ofPixelsBitmapSource::isRotateSupported() const {
  return false;
}

Ref<LuminanceSource> ofPixelsBitmapSource::rotateCounterClockwise() {
  return Ref<ofPixelsBitmapSource> (NULL);
}

}

