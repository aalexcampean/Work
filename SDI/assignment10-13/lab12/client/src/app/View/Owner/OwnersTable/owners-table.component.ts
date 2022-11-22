import {Component, Input, OnInit} from '@angular/core';
import {MdbModalRef, MdbModalService} from "mdb-angular-ui-kit/modal";
import {OwnerService} from "../../../Controller/owner-service";
import {OwnerDTO} from "../../../Model/ownerDTO";
import {OwnersModalComponent} from "../OwnersModal/owners-modal.component";
import {PetsModalComponent} from "../../ReusableComponents/PetsModal/pets-modal.component";
import {PetDTO} from "../../../Model/petDTO";

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

  constructor(private ownerService: OwnerService, private modalAddUpdateService: MdbModalService, private modalPetsService: MdbModalService) {
  }

  ngOnInit(): void {
    this.getOwners();
  }

  public getOwners(): void {
    this.ownerService.getAllOwners()
      .subscribe(owner => this.owners = owner.owners);
  }

  public addOwner(owner: OwnerDTO): void {
    this.ownerService.addOwner(owner);
    this.owners.push(owner);
  }

  public deleteOwner(id: number): void {
    this.ownerService.deleteOwner(id);
    this.owners = this.owners.filter((document) => document.id != id);
  }

  public updateOwner(owner: OwnerDTO): void {
    this.ownerService.updateOwner(owner);

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
