import {Component, Input, OnInit} from '@angular/core';
import {ChannelDTO} from "../../Model/channelDTO";
import {ChannelService} from "../../Service/channel-service";
import {MdbModalRef, MdbModalService} from "mdb-angular-ui-kit/modal";

@Component({
    selector: 'subscriptions-table',
    templateUrl: './subscriptions-table.component.html',
    styleUrls: ['./subscriptions-table.component.css']
})
export class SubscriptionsTableComponent implements OnInit {
    title = 'Subscriptions';
    ownerChannels: Array<ChannelDTO> = [];
    userChannels: Array<ChannelDTO> = [];
    ownerNameInput = "";
    currentUser = sessionStorage.getItem('username');

    constructor(private channelService: ChannelService, private modalService: MdbModalService) {
    }

    ngOnInit(): void {
        this.getChannels();
        this.getChannelsByCurrentUser();
    }

    getChannels(): void {
        this.channelService.getAllChannels()
            .subscribe(channels => this.ownerChannels = channels);
    }

    getChannelsByOwnerName(): void {
        this.channelService.getAllChannelsByOwner(this.ownerNameInput)
            .subscribe(channels => {
                this.ownerChannels = channels;
            });
    }

    getChannelsByCurrentUser(): void {
        this.channelService.getAllChannelsByUser(this.currentUser!)
            .subscribe(channels => {
                this.userChannels = channels;
            });
    }

    subscribeToChannel(channel: ChannelDTO): void {
        this.channelService.subscribeUserToChannel(this.currentUser!, channel);
        this.getChannels();
    }
}
