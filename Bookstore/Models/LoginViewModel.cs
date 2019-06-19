namespace Bookstore.Models
{
   using System;
   using System.Collections.Generic;
   using System.ComponentModel.DataAnnotations;
   using System.Linq;
   using System.Web;

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