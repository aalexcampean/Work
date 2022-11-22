import {Component, Input, OnInit} from '@angular/core';
import {MdbModalRef, MdbModalService} from "mdb-angular-ui-kit/modal";
import {PetDTO} from "../../../Model/petDTO";
import {AddUpdatePetsModalComponent} from "../AddUpdatePetsModal/add-update-pets-modal.component";
import {PetService} from "../../../Controller/pet-service";
import {PetsOwnerModalComponent} from "../PetsOwnerModal/pets-owner-modal.component";
import {OwnerDTO} from "../../../Model/ownerDTO";
import {AppointmentDTO} from "../../../Model/appointmentDTO";
import {AppointmentsModalComponent} from "../../ReusableComponents/AppointmentsModal/appointments-modal.component";

@Component({
  selector: 'pets-table',
  templateUrl: './pets-table.component.html',
  styleUrls: ['./pets-table.component.css', "../../ReusableComponents/ReusableStyling/TableStyling.css"]
})
export class PetsTableComponent implements OnInit {
  pets: Array<PetDTO> = [];
  owner: OwnerDTO | null = null;
  appointments: Array<AppointmentDTO> = [];
  modalAddUpdateRef: MdbModalRef<AddUpdatePetsModalComponent> | null = null;
  modalOwnerRef: MdbModalRef<PetsOwnerModalComponent> | null = null;
  modalAppointmentsRef: MdbModalRef<AppointmentsModalComponent> | null = null;

  constructor(private petService: PetService, private modalAddUpdateService: MdbModalService,
              private modalOwnerService: MdbModalService, private modalAppointmentsService: MdbModalService) {
  }

  ngOnInit(): void {
    this.getPets();
  }

  public getPets(): void {
    this.petService.getAllPets()
      .subscribe(pets => this.pets = pets.pets);
  }

  public addPet(pet: PetDTO): void {
    this.petService.addPet(pet);
    this.pets.push(pet);
  }

  public deletePet(id: number): void {
    this.petService.deletePet(id);
    this.pets = this.pets.filter((pet) => pet.id != id);
  }

  public updatePet(pet: PetDTO): void {
    this.petService.updatePet(pet);
  }

  public openModalForAdd(): void {
    this.modalAddUpdateRef = this.modalAddUpdateService.open(AddUpdatePetsModalComponent, {
      modalClass: 'modal-lg'
    });
    this.modalAddUpdateRef.onClose.subscribe((response: PetDTO | string) => {
      if (typeof response === "string") {
      } else {
        this.addPet(response);
      }
    });
  }

  public openModalForUpdate(pet: PetDTO): void {
    this.modalAddUpdateRef = this.modalAddUpdateService.open(AddUpdatePetsModalComponent, {
      data: {
        inputId: pet.id,
        inputSpecies: pet.species,
        inputBreed: pet.breed,
        inputName: pet.name,
        inputDateOfEnrolment: pet.dateOfEnrolment,
        inputOwnerId: pet.ownerId
      },
      modalClass: 'modal-lg'
    });
    this.modalAddUpdateRef.onClose.subscribe((response: PetDTO | string) => {
      if (typeof response === "string") {
      } else {
        this.updatePet(response);
      }
    });
  }

  public openOwnerModal(id: number): void {
    this.petService.getPetOwner(id)
      .subscribe(owner => {
        this.owner = owner
        this.modalOwnerRef = this.modalOwnerService.open(PetsOwnerModalComponent, {
          data: {
            owner: this.owner
          },
          modalClass: 'modal-lg'
        });
      });
  }

  public openAppointmentsModal(id: number): void {
    this.petService.getPetAppointments(id)
      .subscribe(appointments => {
        this.appointments = appointments.appointments
        this.modalAppointmentsRef = this.modalAppointmentsService.open(AppointmentsModalComponent, {
          data: {
            appointments: this.appointments
          },
          modalClass: 'modal-lg'
        });
      });
  }
}
