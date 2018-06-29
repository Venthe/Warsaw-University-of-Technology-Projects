namespace Bookstore.Models
{
   using System.ComponentModel.DataAnnotations;
   using System.ComponentModel.DataAnnotations.Schema;

   public class Session
   {
      [Key]
      [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
      public int SessionId { get; set; }

      [Required]
      [StringLength(450)]
      [Index("IX_UniqueHobbyCode", IsUnique = true)]
      public string Key { get; set; }

      public virtual User User { get; set; }
   }
}