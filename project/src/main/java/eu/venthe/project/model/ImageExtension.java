package eu.venthe.project.model;

public enum ImageExtension {
  JPG,
  PNG,
  TIF,
  BMP;

  public static ImageExtension returnExtensionFromString(String input) {
    ImageExtension result = null;
    if (input.toLowerCase().equals("jpg") || input.toLowerCase().equals("jpeg")) {
      result = ImageExtension.JPG;
    } else if (input.toLowerCase().equals("png")) {
      result = ImageExtension.PNG;
    } else if (input.toLowerCase().equals("tif") || input.toLowerCase().equals("tiff")) {
      result = ImageExtension.TIF;
    } else if (input.toLowerCase().equals("bmp")) {
      result = ImageExtension.BMP;
    }
    return result;
  }
}
