namespace Bookstore.Models
{
   using System.Collections.Generic;
   using System.ComponentModel.DataAnnotations;
   using System.ComponentModel.DataAnnotations.Schema;

   public class Hobby
   {

      [Required]
      [StringLength(450)]
      [Index("IX_UniqueHobbyCode", IsUnique = true)]
      public string Code { get; set; }
      [Key]
      [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
      public int HobbyId { get; set; }

      public virtual ICollection<User> Users { get; set; } = new HashSet<User>();
   }
}