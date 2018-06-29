namespace Bookstore.Models
{
   using System.Collections.Generic;
   using System.ComponentModel.DataAnnotations;
   using System.ComponentModel.DataAnnotations.Schema;

   public class UserRole
   {
      [Required]
      [StringLength(450)]
      [Index("IX_UniqueHobbyCode", IsUnique = true)]
      public string RoleName { get; set; }

      [Key]
      [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
      public int UserRoleId { get; set; }

      public virtual ICollection<User> Users { get; set; } = new HashSet<User>();
   }
}