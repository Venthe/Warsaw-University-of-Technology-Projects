namespace Bookstore.Models
{
   using System.Collections.Generic;
   using System.ComponentModel.DataAnnotations;
   using System.ComponentModel.DataAnnotations.Schema;

   public class Hobby
   {
      [Key]
      [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
      public int HobbyId { get; set; }

      [Required]
      [StringLength(450)]
      [Index("IX_UniqueHobbyCode", IsUnique = true)]
      public string Code { get; set; }

      public ICollection<User> Users { get; set; } = new HashSet<User>();
   }
}