#include <iostream>
#include "group.h"

namespace Mango{
	namespace Core{

		/*
		    Group
		                */
		
		/* Static Members */
		int Group::BOC_TYPE_ID = -1;
		
		/* Constructors, Destructors */
		
		Group::Group():Object(){
		    // If not already registered, register the Group object as a BOC type
		    if (Group::BOC_TYPE_ID == -1){
		        Group::BOC_TYPE_ID = Object::createObjectContainerType();
		    }
		}		
		
		Group::~Group(){
		    // Pass
		}
		
		
		
		/* Member Access Functions */
		bool Group::add(Object *new_member){
		    if (new_member == NULL){
		        throw ValueError(objectType(), "addMember", "new member cannot be NULL");
		    }
		
		    // Don't add a member that's already a member
		    if (includes(new_member)){
		        throw ValueError(objectType(), "addMember", "Can't add existing member");
		    }
		
		    // Add the new member
		    members.push_back(new_member);
		
		    // Store the record in the object's objectContainers list
		    if (new_member->objectContainers.capacity() <= Group::BOC_TYPE_ID){
		        new_member->objectContainers.reserve(Group::BOC_TYPE_ID + 1);
		    }
		
		    new_member->objectContainers[Group::BOC_TYPE_ID].first = members.size() - 1;
		    new_member->objectContainers[Group::BOC_TYPE_ID].second = this;
		    return true;
		}
		
		bool Group::remove(Object* bad_member){
		    int bad_member_id, member_list_size;
		
		    if (bad_member == NULL){
		        throw ValueError(objectType(), "remove", "cannot remove NULL value");
		    }
		
		    if (bad_member->objectContainers.capacity() <= Group::BOC_TYPE_ID){
		        return false;
		    }
		
		    bad_member_id = bad_member->objectContainers[Group::BOC_TYPE_ID].first;
		    if (bad_member_id > -1 && bad_member->objectContainers[Group::BOC_TYPE_ID].second == this){
		        member_list_size = members.size();
		
		        if (bad_member_id == member_list_size - 1){
		            // Just erase it, ids present no problem
		            members.pop_back();
		        }
		        else{
		            // Copy the last member to the position of the bad member
		            members[bad_member_id] = members[members.size()-1];
		
		            // Change the id of what was previously the last member
		            members[bad_member_id]->objectContainers[Group::BOC_TYPE_ID].first = bad_member_id;
		
		            // Pop the last member
		            members.pop_back();
		        }
		        bad_member->objectContainers[Group::BOC_TYPE_ID].first = -1;
		
		        return true;
		    }
		    return false;
		}
		
		void Group::removeAt(int index){
		    int member_list_size;
		    member_list_size = members.size();
		
		    if (index < 0 || index >= member_list_size){
		        throw ValueError(objectType(), "removeAt", "invalid index");
		    }
		
		    if (index != member_list_size - 1){
		        members[index] = members[member_list_size - 1];
		    }
		    members.pop_back();
		}
		
		bool Group::includes(Object* suspect_member){
		    if (suspect_member == NULL){
		        throw ValueError(objectType(), "isMember", "cannot test for membership of NULL object");
		    }
		
		    if (suspect_member->objectContainers.capacity() <= Group::BOC_TYPE_ID){
		        return false;
		    }
		
		    if ((suspect_member->objectContainers[Group::BOC_TYPE_ID].second == this) && (suspect_member->objectContainers[Group::BOC_TYPE_ID].first > -1)){
		        return true;
		    }
		    return false;
		}
		
		void Group::removeBasicObject(Object* object_to_remove, int BOCT_ID){
		    remove(object_to_remove);
		}
		
		
		
		
		/*  Events */
		
		void Group::render(){
		    executeRenderEvents();
		}
		
		void Group::draw(){
		    executeDrawEvents();
		}
		
		void Group::pre_step(){
		    executePreStepEvents();
		}
		
		void Group::step(){
		    executeStepEvents();
		}
		
		void Group::post_step(){
		    executePostStepEvents();
		}

		void Group::input(inputEvent &event){
		    executeInputEvents(event);
		}
		
		
		
		
		
		void Group::executePreStepEvents(){
		    std::vector<Object*>::iterator member;
		
		    for (member = members.begin(); member != members.end(); member ++){
		        (*member)->pre_step();
		    }
		}
		
		void Group::executeStepEvents(){
		    std::vector<Object*>::iterator member;
		
		    for (member = members.begin(); member != members.end(); member ++){
		        (*member)->step();
		    }
		
		}
		
		void Group::executePostStepEvents(){
		    std::vector<Object*>::iterator member;
		
		    for (member = members.begin(); member != members.end(); member ++){
		        (*member)->post_step();
		    }
		}		
		
		void Group::executeRenderEvents(){
		    std::vector<Object*>::iterator member;
			
		    glPushMatrix();
		    
		    glTranslated(position[0], position[1], position[2]);
		
		    glRotated(angle_alpha, u1[0], u1[1], u1[2]);
		    glRotated(angle_beta, u2[0], u2[1], u2[2]);
		    glRotated(angle_gamma, u3[0], u3[1], u3[2]);
		
		    glTranslated(displacement[0], displacement[1], displacement[2]);
		
		
		        for (member = members.begin(); member != members.end(); member ++){
		            glPushMatrix();
		            (*member)->render();
		            glPopMatrix();
		        }
		
		    glPopMatrix();
		}
		
		void Group::executeDrawEvents(){
		    std::vector<Object*>::iterator member;
		
		    glTranslated(position[0], position[1], position[2]);
		
		    glRotated(angle_alpha, u1[0], u1[1], u1[2]);
		    glRotated(angle_beta, u2[0], u2[1], u2[2]);
		    glRotated(angle_gamma, u3[0], u3[1], u3[2]);
		
		    glTranslated(displacement[0], displacement[1], displacement[2]);
		
		
		        for (member = members.begin(); member != members.end(); member ++){
		            glPushMatrix();
		            (*member)->draw();
		            glPopMatrix();
		        }
		}
		
		
		void Group::executeInputEvents(inputEvent &event){
		    std::vector<Object*>::iterator member;
		
		    for (member = members.begin(); member != members.end(); member ++){
		        (*member)->input(event);
		    }
		}
		
		
	} // Core
} // Mango

