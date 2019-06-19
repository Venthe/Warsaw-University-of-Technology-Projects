namespace Bookstore.Models
{
   using System.Collections.Generic;
   using System.ComponentModel.DataAnnotations;
   using System.ComponentModel.DataAnnotations.Schema;

   public class User
   {
      [Key]
      [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
      public int UserId { get; set; }

      [Display(Name = "Username")]
      [Required(ErrorMessage = "The username is required")]
      public string Username { get; set; }

      // TODO Crypto
      [Display(Name = "Password")]
      [MinLength(8, ErrorMessage = "Password must be at least {1} letters long")]
      [DataType(DataType.Password)]
      [Required(ErrorMessage = "The password is required")]
      public string Password { get; set; }

      [Display(Name = "Name")]
      [Required(ErrorMessage = "The name is required")]
      public string Name { get; set; }

      [Display(Name = "Surname")]
      [Required(ErrorMessage = "The surname is required")]
      public string Surname { get; set; }

      [Display(Name = "Email address")]
      [Required(ErrorMessage = "The email address is required")]
      [EmailAddress(ErrorMessage = "Invalid Email Address")]
      public string Email { get; set; }

      public int EducationId { get; set; }

      public Education Education { get; set; }

      [Index("IX_UniqueAddressId", IsUnique = true)]
      public int AddressId { get; set; }

      public Address Address { get; set; }

      public ICollection<Hobby> Hobbies { get; set; } = new HashSet<Hobby>();

      public virtual ICollection<UserRole> Users { get; set; } = new HashSet<UserRole>();
   }
}