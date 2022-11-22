using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace AcademicInfoAPI.Data.Migrations
{
    public partial class v5 : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_CurriculumContracts_ContractsOfStudies_CurriculumID",
                table: "CurriculumContracts");

           
            migrationBuilder.CreateIndex(
                name: "IX_CurriculumContracts_ContractID",
                table: "CurriculumContracts",
                column: "ContractID");

            migrationBuilder.AddForeignKey(
                name: "FK_CurriculumContracts_ContractsOfStudies_ContractID",
                table: "CurriculumContracts",
                column: "ContractID",
                principalTable: "ContractsOfStudies",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_CurriculumContracts_ContractsOfStudies_ContractID",
                table: "CurriculumContracts");

            migrationBuilder.DropIndex(
                name: "IX_CurriculumContracts_ContractID",
                table: "CurriculumContracts");

           

            migrationBuilder.AddForeignKey(
                name: "FK_CurriculumContracts_ContractsOfStudies_CurriculumID",
                table: "CurriculumContracts",
                column: "CurriculumID",
                principalTable: "ContractsOfStudies",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);
        }
    }
}
