namespace Bookstore.Models
{
   using System.ComponentModel.DataAnnotations;

   public class LoginViewModel
   {
      [Display(Name = "Username")]
      [Required(ErrorMessage = "The username is required")]
      public string Username { get; set; }

      // TODO Crypto
      [Display(Name = "Password")]
      [MinLength(8, ErrorMessage = "Password must be at least {1} letters long")]
      [DataType(DataType.Password)]
      [Required(ErrorMessage = "The password is required")]
      public string Password { get; set; }
   }
}