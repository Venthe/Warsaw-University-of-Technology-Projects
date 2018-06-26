using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Web;

namespace Bookstore.Models
{
   public class Address
   {
      [Key, DatabaseGenerated(DatabaseGeneratedOption.Identity)]
      public int AddressId { get; set; }

      [Display(Name = "Country"), Required]
      public String Country { get; set; }

      [Display(Name = "County")]
      public String County { get; set; }

      [Display(Name = "City"), Required]
      public String City { get; set; }

      [Display(Name = "Street"), Required]
      public String Street { get; set; }

      [Display(Name = "Flat number"), Required]
      public String FlatNumber { get; set; }

      [Display(Name = "Apartment number")]
      public String ApartamentNumber { get; set; }

      public ICollection<User> Users { get; set; } = new HashSet<User>();
   }
}