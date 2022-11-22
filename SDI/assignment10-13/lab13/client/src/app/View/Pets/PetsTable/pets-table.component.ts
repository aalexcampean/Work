import {Component, OnInit} from '@angular/core';
import {MdbModalRef, MdbModalService} from "mdb-angular-ui-kit/modal";
import {PetDTO} from "../../../Model/petDTO";
import {AddUpdatePetsModalComponent} from "../AddUpdatePetsModal/add-update-pets-modal.component";
import {PetService} from "../../../Controller/pet-service";
import {PetsOwnerModalComponent} from "../PetsOwnerModal/pets-owner-modal.component";
import {OwnerDTO} from "../../../Model/ownerDTO";
import {AppointmentDTO} from "../../../Model/appointmentDTO";
import {AppointmentsModalComponent} from "../../ReusableComponents/AppointmentsModal/appointments-modal.component";
import {OwnerService} from "../../../Controller/owner-service";
import {BirthCertificatesService} from "../../../Controller/birth-certificates-service";
import {BirthCertificateModalComponent} from "../BirthCertificateModal/birth-certificate-modal.component";
import {BirthCertificateDTO} from "../../../Model/birthCertificateDTO";
import {UntilDestroy, untilDestroyed} from "@ngneat/until-destroy";
import {tap} from "rxjs";

@UntilDestroy()
@Component({
  selector: 'pets-table',
  templateUrl: './pets-table.component.html',
  styleUrls: ['./pets-table.component.css', "../../ReusableComponents/ReusableStyling/TableStyling.css"]
})
export class PetsTableComponent implements OnInit {
  owner: OwnerDTO | null = null;
  pets: Array<PetDTO> = [];
  owners: Array<OwnerDTO> = [];
  appointments: Array<AppointmentDTO> = [];
  birthCertificates: Array<BirthCertificateDTO> = [];
  modalAddUpdateRef: MdbModalRef<AddUpdatePetsModalComponent> | null = null;
  modalOwnerRef: MdbModalRef<PetsOwnerModalComponent> | null = null;
  modalAppointmentsRef: MdbModalRef<AppointmentsModalComponent> | null = null;
  modalBirthCertificateRef: MdbModalRef<BirthCertificateModalComponent> | null = null;
  pageNumber = 1;
  pageSize = 5;
  count = 0;

  constructor(private petService: PetService, private ownerService: OwnerService, private birthCertificateService: BirthCertificatesService,
              private modalAddUpdateService: MdbModalService, private modalOwnerService: MdbModalService,
              private modalAppointmentsService: MdbModalService, private modalBirthCertificateService: MdbModalService) {
  }

  ngOnInit(): void {
    this.getPets();
    this.getOwners();
    this.getBirthCertificates();
  }

  handlePageChange(event: any): void {
    this.pageNumber = event;
    this.ngOnInit();
  }

  public getPets(): void {
    this.petService.getAllPaginatedPets(this.pageNumber, this.pageSize)
      .pipe(
        untilDestroyed(this),
        tap((pets) => {
          this.pets = pets.pets;
          this.count = pets.total;
          this.pets = this.pets.sort((a, b) => a.id - b.id);
        })
      )
      .subscribe(pets => this.pets = pets.pets);
  }

  public getOwners(): void {
    this.ownerService.getAllOwners()
      .subscribe(owners => this.owners = owners.owners);
  }

  public getBirthCertificates(): void {
    this.birthCertificateService.getAllBirthCertificates()
      .subscribe(birthCertificates => this.birthCertificates = birthCertificates.birthCertificates);
  }

  public getBirthCertificateByPetId(id: number): BirthCertificateDTO | null {
    const birthCertificate = this.birthCertificates.find(function (birthCertificate) {
      return birthCertificate.petId === id;
    });
    return birthCertificate == null? null : birthCertificate;
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
    let updatedPet = this.pets.find(function (oldPet) {
      return oldPet.id === pet.id;
    });
    this.petService.updatePet(pet);
    let index = this.pets.indexOf(updatedPet!);
    this.pets[index] = pet;
  }

  public addBirthCertificate(birthCertificate: BirthCertificateDTO): void {
    this.birthCertificateService.addBirthCertificate(birthCertificate);
  }

  public updateBirthCertificate(birthCertificate: BirthCertificateDTO): void {
    this.birthCertificateService.updateBirthCertificate(birthCertificate);
  }

  public deleteBirthCertificate(petId: number): void {
    const birthCertificate = this.getBirthCertificateByPetId(petId);
    if (birthCertificate != null) {
      this.birthCertificateService.deleteBirthCertificate(birthCertificate.id);
    }
  }

  public openModalForAdd(): void {
    this.modalAddUpdateRef = this.modalAddUpdateService.open(AddUpdatePetsModalComponent, {
      data: {
        owners: this.owners
      },
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
        owners: this.owners,
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

  public openBirthCertificateModalForAdd(id: number): void {
    this.modalBirthCertificateRef = this.modalBirthCertificateService.open(BirthCertificateModalComponent, {
      data: {
        inputPetId: id
      },
      modalClass: 'modal-lg'
    });
    this.modalBirthCertificateRef.onClose.subscribe((response: BirthCertificateDTO | string) => {
      if (typeof response === "string") {
      } else {
        this.addBirthCertificate(response);
      }
    });
  }

  public openBirthCertificateModalForUpdate(petId: number): void {
    const birthCertificate = this.getBirthCertificateByPetId(petId);
    if (birthCertificate != null) {
      this.modalBirthCertificateRef = this.modalBirthCertificateService.open(BirthCertificateModalComponent, {
        data: {
          pets: this.pets,
          showPets: true,
          inputId: birthCertificate.id,
          inputText: birthCertificate.text,
          inputLocation: birthCertificate.location,
          inputDate: birthCertificate.date,
          inputHealthGrade: birthCertificate.healthGrade,
          inputPetId: birthCertificate.petId
        },
        modalClass: 'modal-lg'
      });
      this.modalBirthCertificateRef.onClose.subscribe((response: BirthCertificateDTO | string) => {
        if (typeof response === "string") {
        } else {
          this.updateBirthCertificate(response);
        }
      });
    }
  }
}
