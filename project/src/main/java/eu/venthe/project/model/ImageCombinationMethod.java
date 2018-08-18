package eu.venthe.project.model;

public enum ImageCombinationMethod {
  AND,
  OR,
  XOR;

  public static ImageCombinationMethod returnTypeFromString(String input) {
    ImageCombinationMethod result = null;
    if (input.toLowerCase().equals("and")) {
      result = ImageCombinationMethod.AND;
    } else if (input.toLowerCase().equals("or")) {
      result = ImageCombinationMethod.OR;
    } else if (input.toLowerCase().equals("xor")) {
      result = ImageCombinationMethod.XOR;
    }
    return result;
  }
}
