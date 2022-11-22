import {Component, Input, OnInit} from '@angular/core';
import {MdbModalRef, MdbModalService} from "mdb-angular-ui-kit/modal";
import {OwnerService} from "../../../Controller/owner-service";
import {OwnerDTO} from "../../../Model/ownerDTO";
import {OwnersModalComponent} from "../OwnersModal/owners-modal.component";
import {PetsModalComponent} from "../../ReusableComponents/PetsModal/pets-modal.component";
import {PetDTO} from "../../../Model/petDTO";
import {UntilDestroy, untilDestroyed} from "@ngneat/until-destroy";
import {tap} from "rxjs";
import {NavigationExtras, Router} from '@angular/router';

@UntilDestroy()
@Component({
  selector: 'owners-table',
  templateUrl: './owners-table.component.html',
  styleUrls: ['./owners-table.component.css', "../../ReusableComponents/ReusableStyling/TableStyling.css"]
})
export class OwnersTableComponent implements OnInit{
  owners: Array<OwnerDTO> = [];
  pets: Array<PetDTO> = [];
  modalAddUpdateRef: MdbModalRef<OwnersModalComponent> | null = null;
  modalPetsRef: MdbModalRef<PetsModalComponent> | null = null;
  pageNumber = 1;
  pageSize = 5;
  count = 0;
  inputDeleteByFirstName: string | null = null;

  constructor(private ownerService: OwnerService, private modalAddUpdateService: MdbModalService, private modalPetsService: MdbModalService, private router: Router) {
  }

  ngOnInit(): void {
    this.getOwners();
  }

  handlePageChange(event: any): void {
    this.pageNumber = event;
    this.ngOnInit();
  }

  public getOwners(): void {
    this.ownerService.getAllPaginatedOwners(this.pageNumber, this.pageSize)
      .pipe(
        untilDestroyed(this),
        tap((owners) => {
          this.owners = owners.owners;
          this.count = owners.total;
          this.owners = this.owners.sort((a, b) => a.id - b.id);
        })
      )
      .subscribe(owners => this.owners = owners.owners);
  }

  public addOwner(owner: OwnerDTO): void {
    this.ownerService.addOwner(owner);
    this.owners.push(owner);
  }

  public deleteOwner(id: number): void {
    this.ownerService.deleteOwner(id);
    this.owners = this.owners.filter((owner) => owner.id != id);
  }

  public goToDelete() : void {
    this.router.navigate(['/delete-owners']);
  }

  public updateOwner(owner: OwnerDTO): void {
    let updatedOwner = this.owners.find(function (oldOwner) {
      return oldOwner.id === owner.id;
    });
    this.ownerService.updateOwner(owner);
    let index = this.owners.indexOf(updatedOwner!);
    this.owners[index] = owner;
  }

  public openModalForAdd(): void {
    this.modalAddUpdateRef = this.modalAddUpdateService.open(OwnersModalComponent, {
      modalClass: 'modal-lg'
    });
    this.modalAddUpdateRef.onClose.subscribe((response: OwnerDTO | string) => {
      if (typeof response === "string") {
      } else {
        this.addOwner(response);
      }
    });
  }

  public openModalForUpdate(owner: OwnerDTO): void {
    this.modalAddUpdateRef = this.modalAddUpdateService.open(OwnersModalComponent, {
      data: {
        inputId: owner.id,
        inputFirstName: owner.firstName,
        inputLastName: owner.lastName,
        inputEmail: owner.email,
        inputPhoneNumber: owner.phoneNumber,
        inputDateOfBirth: owner.dateOfBirth
      },
      modalClass: 'modal-lg'
    });
    this.modalAddUpdateRef.onClose.subscribe((response: OwnerDTO | string) => {
      if (typeof response === "string") {
      } else {
        this.updateOwner(response);
      }
    });
  }

  public openPetsModal(id: number): void {
    this.ownerService.getOwnerPets(id)
      .subscribe(pets => {
        this.pets = pets.pets
        this.modalPetsRef = this.modalPetsService.open(PetsModalComponent, {
          data: {
            pets: this.pets
          },
          modalClass: 'modal-lg'
        });
      });
  }
}
