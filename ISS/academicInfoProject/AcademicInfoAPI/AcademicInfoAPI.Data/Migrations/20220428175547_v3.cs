using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace AcademicInfoAPI.Data.Migrations
{
    public partial class v3 : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_ContractOfStudy_Curriculum_CurriculumID",
                table: "ContractOfStudy");

            migrationBuilder.DropIndex(
                name: "IX_ContractOfStudy_CurriculumID",
                table: "ContractOfStudy");

            migrationBuilder.DropIndex(
                name: "IX_ContractOfStudy_UserID",
                table: "ContractOfStudy");

            migrationBuilder.CreateTable(
                name: "CurriculumContract",
                columns: table => new
                {
                    CurriculumID = table.Column<int>(type: "int", nullable: false),
                    ContractID = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_CurriculumContract", x => new { x.CurriculumID, x.ContractID });
                    table.ForeignKey(
                        name: "FK_CurriculumContract_ContractOfStudy_CurriculumID",
                        column: x => x.CurriculumID,
                        principalTable: "ContractOfStudy",
                        principalColumn: "ID",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "FK_CurriculumContract_Curriculum_CurriculumID",
                        column: x => x.CurriculumID,
                        principalTable: "Curriculum",
                        principalColumn: "ID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateIndex(
                name: "IX_ContractOfStudy_UserID",
                table: "ContractOfStudy",
                column: "UserID",
                unique: true,
                filter: "[UserID] IS NOT NULL");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "CurriculumContract");

            migrationBuilder.DropIndex(
                name: "IX_ContractOfStudy_UserID",
                table: "ContractOfStudy");

            migrationBuilder.CreateIndex(
                name: "IX_ContractOfStudy_CurriculumID",
                table: "ContractOfStudy",
                column: "CurriculumID");

            migrationBuilder.CreateIndex(
                name: "IX_ContractOfStudy_UserID",
                table: "ContractOfStudy",
                column: "UserID");

            migrationBuilder.AddForeignKey(
                name: "FK_ContractOfStudy_Curriculum_CurriculumID",
                table: "ContractOfStudy",
                column: "CurriculumID",
                principalTable: "Curriculum",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);
        }
    }
}
