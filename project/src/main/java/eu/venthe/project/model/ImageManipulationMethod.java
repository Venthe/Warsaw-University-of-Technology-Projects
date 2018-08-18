package eu.venthe.project.model;

public enum ImageManipulationMethod {
  CENTER,
  ENLARGE,
  SHRINK,
  CUTOUT;

  public static ImageManipulationMethod returnMethodFromString(String input) {
    ImageManipulationMethod result = null;
    if (input.toLowerCase().equals("center") || input.toLowerCase().equals("center images")) {
      result = ImageManipulationMethod.CENTER;
    } else if (input.toLowerCase().equals("enlarge") || input.toLowerCase()
        .equals("resize (enlarge)")) {
      result = ImageManipulationMethod.ENLARGE;
    } else if (input.toLowerCase().equals("shrink") || input.toLowerCase()
        .equals("resize (shrink)")) {
      result = ImageManipulationMethod.SHRINK;
    } else if (input.toLowerCase().equals("cutout") || input.toLowerCase().equals("cut out")) {
      result = ImageManipulationMethod.CUTOUT;
    }
    return result;
  }
}
