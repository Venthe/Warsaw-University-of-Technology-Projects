namespace Bookstore.Models
{
   using System.Collections.Generic;
   using System.ComponentModel.DataAnnotations;
   using System.ComponentModel.DataAnnotations.Schema;

   public class Education
   {
      [Key]
      [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
      public int EducationId { get; set; }

      [Required]
      [StringLength(450)]
      [Index("IX_UniqueEducationCode", IsUnique = true)]
      public string Code { get; set; }

      public ICollection<User> Users { get; set; } = new HashSet<User>();
   }
}