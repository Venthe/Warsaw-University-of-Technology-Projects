namespace Bookstore.Models
{
   using System.ComponentModel.DataAnnotations;
   using System.Web;

   public class UserLogin
   {
      [Display(Name = "Username")]
      [Required(ErrorMessage = "The username is required")]
      public string Username
      {
         get => HttpContext.Current.Application["username"] as string;
         set => HttpContext.Current.Application["username"] = value;
      }

      // TODO Crypto
      [Display(Name = "Password")]
      [MinLength(8, ErrorMessage = "Password must be at least {1} letters long")]
      [DataType(DataType.Password)]
      [Required(ErrorMessage = "The password is required")]
      public string Password
      {
         get => HttpContext.Current.Application["password"] as string;
         set => HttpContext.Current.Application["password"] = value;
      }
   }
}