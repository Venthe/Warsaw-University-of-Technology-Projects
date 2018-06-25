using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace Bookstore.Models.User
{
   public class Address
   {
      [Display(Name = "Country")]
      [Required]
      String Country { get; set; }

      [Display(Name = "County")]
      String County { get; set; }

      [Display(Name = "City")]
      [Required]
      String City { get; set; }

      [Display(Name = "Street")]
      [Required]
      String Street { get; set; }

      [Display(Name = "Flat number")]
      [Required]
      String FlatNumber { get; set; }

      [Display(Name = "Aoartament number")]
      String ApartamentNumber { get; set; }
   }
}