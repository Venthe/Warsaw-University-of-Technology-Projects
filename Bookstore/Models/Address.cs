namespace Bookstore.Models
{
   using System.Collections.Generic;
   using System.ComponentModel.DataAnnotations;
   using System.ComponentModel.DataAnnotations.Schema;

   public class Address
   {
      [Key]
      [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
      public int AddressId { get; set; }

      [Display(Name = "Country")]
      [Required]
      public string Country { get; set; }

      [Display(Name = "County")]
      public string County { get; set; }

      [Display(Name = "City")]
      [Required]
      public string City { get; set; }

      [Display(Name = "Street")]
      [Required]
      public string Street { get; set; }

      [Display(Name = "Flat number")]
      [Required]
      public string FlatNumber { get; set; }

      [Display(Name = "Apartment number")]
      public string ApartamentNumber { get; set; }

      public virtual ICollection<User> Users { get; set; } = new HashSet<User>();
   }
}