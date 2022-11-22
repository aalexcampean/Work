import {Component, Input, OnInit} from '@angular/core';
import {ProjectDTO} from "../../Model/projectDTO";
import {ProjectService} from "../../Service/project.service";
import {MdbModalRef, MdbModalService} from "mdb-angular-ui-kit/modal";
import {ProjectsModalComponent} from "../ProjectsModal/projects-modal.component";
import {SendDTO} from "../../Model/sendDTO";

@Component({
    selector: 'projects-table',
    templateUrl: './projects-table.component.html',
    styleUrls: ['./projects-table.component.css']
})
export class ProjectsTableComponent implements OnInit {
    title = 'Subscriptions';
    allProjects: Array<ProjectDTO> = [];
    userProjects: Array<ProjectDTO> = [];
    currentUser = sessionStorage.getItem('username');
    modalProjectRef: MdbModalRef<ProjectsModalComponent> | null = null;

    constructor(private channelService: ProjectService, private modalService: MdbModalService) {
    }

    ngOnInit(): void {
        this.getProjects();
        this.getProjectsByUserName();
    }

    getProjects(): void {
        this.channelService.getAllProjects()
            .subscribe(projects => this.allProjects = projects);
    }

    getProjectsByUserName(): void {
        this.channelService.getAllChannelsByUser(this.currentUser!)
            .subscribe(projects => {
                this.userProjects = projects;
            });
    }

    addMemberToProjects(data: SendDTO): void {
        this.channelService.addMemberToProjects(data.memberName, data.projects);
        this.getProjects();
    }

    public openModalForAdd(): void {
        this.modalProjectRef = this.modalService.open(ProjectsModalComponent, {
            modalClass: 'modal-lg'
        });
        this.modalProjectRef.onClose.subscribe((response: SendDTO | string) => {
            if (typeof response === "string") {
            } else {
                this.addMemberToProjects(response);
            }
        });
    }
}
