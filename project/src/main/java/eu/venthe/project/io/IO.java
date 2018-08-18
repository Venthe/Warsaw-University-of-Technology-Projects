package eu.venthe.project.io;

import com.sun.media.jai.codec.FileSeekableStream;
import com.sun.media.jai.codec.TIFFDecodeParam;
import eu.venthe.project.model.ImageExtension;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.awt.image.renderable.ParameterBlock;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import javax.imageio.ImageIO;
import javax.media.jai.JAI;
import javax.media.jai.RenderedOp;

public class IO {
  public static Image loadImageAsImage(String path) {
    // TODO: Various bit sized images are loaded as 8bit
    Image img = null;
    try {
      if (path.endsWith(".tif") || path.endsWith(".tiff")) {
        FileSeekableStream stream = new FileSeekableStream(path);
        TIFFDecodeParam decodeParam = new TIFFDecodeParam();
        decodeParam.setDecodePaletteAsShorts(true);
        ParameterBlock params = new ParameterBlock();
        params.add(stream);
        RenderedOp image1 = JAI.create("tiff", params);
        img = image1.getAsBufferedImage();
      } else {
        img = ImageIO.read(new File(path));
      }
    } catch (IOException e) {
      System.out.println(path);
      e.printStackTrace();
    }
    System.out.println("Image loaded: " + path);

    return img;
  }

  public static void saveArrayOfImages(ArrayList<BufferedImage> img, String path, ImageExtension ext) {
    for (int i = 0; i < img.size(); i++) {
      saveImage(img.get(i), path + "_" + i, ext);
    }
  }

  private static void saveImage(BufferedImage img, String filename, ImageExtension ext) {
    System.out.println("Saving " + filename + "." + ext.toString().toLowerCase());
    //TODO: other formats than PNG
    if (ext.equals(ImageExtension.PNG)) {
      File outputfile = new File(filename + "." + "png");
      try {
        ImageIO.write(img, "png", outputfile);
      } catch (IOException e) {
        e.printStackTrace();
      }
    }
  }
}
