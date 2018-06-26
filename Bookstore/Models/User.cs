using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Web;

namespace Bookstore.Models
{
   // TODO: Move to DB
   public class User
   {
      [Key]
      public String UserId { get; set; }

      [Display(Name = "Username")]
      [Required(ErrorMessage = "The username is required")]
      public String Username { get; set; }

      // TODO Crypto 
      [Display(Name = "Password")]
      [MinLength(8, ErrorMessage = "Password must be at least {1} letters long")]
      [DataType(DataType.Password)]
      [Required(ErrorMessage = "The password is required")]
      public String Password { get; set; }

      [Display(Name = "Name")]
      [Required(ErrorMessage = "The name is required")]
      public String Name { get; set; }

      [Display(Name = "Surname")]
      [Required(ErrorMessage = "The surname is required")]
      public String Surname { get; set; }

      [Display(Name = "Email address")]
      [Required(ErrorMessage = "The email address is required")]
      [EmailAddress(ErrorMessage = "Invalid Email Address")]
      public String Email { get; set; }
      
      // TODO: Add hobbies
      // TODO: Add education
      // TODO: Add detailed address
   }
}