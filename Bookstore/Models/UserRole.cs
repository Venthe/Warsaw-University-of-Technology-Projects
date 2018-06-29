namespace Bookstore.Models
{
   using System;
   using System.Collections.Generic;
   using System.ComponentModel.DataAnnotations;
   using System.ComponentModel.DataAnnotations.Schema;
   using System.Linq;
   using System.Web;

   public class UserRole
   {
      [Key]
      [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
      public int UserRoleId { get; set; }

      [Required]
      [StringLength(450)]
      [Index("IX_UniqueHobbyCode", IsUnique = true)]
      public string RoleName { get; set; }

      public virtual ICollection<User> Users { get; set; } = new HashSet<User>();
   }
}