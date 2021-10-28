void attackCreatureOrOtherPlayer(player &first, player &second) {
    int num;
    std::vector<std::shared_ptr<card>> birinciTasiyici;
    std::vector<std::shared_ptr<card>> ikinciTasiyici;

    std::vector<std::shared_ptr<card>>::iterator birinciOyuncununInplayIteratoru = first.getInplay().begin();
    std::vector<std::shared_ptr<card>>::iterator birinciTasiyicininIteratoru = birinciTasiyici.begin();
    for (int i = 0; i < first.getInplay().size(); i++) {
        if (first.getInplay()[i]->getType() == "Creature" && first.getInplay()[i]->getTap() == false && first.getInplay()[i]->getIsAttack()==false) {

            birinciTasiyici.push_back(first.getInplay()[i]);
            birinciOyuncununInplayIteratoru=first.getInplay().erase(birinciOyuncununInplayIteratoru);
            i-=1;
        } else { birinciOyuncununInplayIteratoru++; }
    }
    std::vector<std::shared_ptr<card>>::iterator birinciTasiyiciIteratoru2 = birinciTasiyici.begin();
    for (int i = 0; i < birinciTasiyici.size(); i++) {
        std::cout << i + 1 << "--> ";
        birinciTasiyici[i]->cardInfo();
        std::cout << std::endl;
    }
    int a;
    a = 0;
    for(int i=0;i<birinciTasiyici.size();i++){

        if(birinciTasiyici[i]->getIsAttack()==false){
            a++;
        }
    }
    if(a ==0){
        std::cout<<"No creature to attack with press a to leave"<<std::endl;
        return;
    }
    else {
        std::cout << "Enter Number Of Creature To Attack With" << std::endl;
        std::cin >> num;
        for (int i = 0; i < num - 1; i++) {
            birinciTasiyiciIteratoru2++;
        }
        ikinciTasiyici.push_back(*birinciTasiyiciIteratoru2);
        birinciTasiyiciIteratoru2 = birinciTasiyici.erase(birinciTasiyiciIteratoru2);
        std::vector<std::shared_ptr<card>>::iterator birinciTasiyiciIteratoru3 = birinciTasiyici.begin();
        for (int i = 0; i < birinciTasiyici.size(); i++) {

            first.getInplay().push_back(*birinciTasiyiciIteratoru3);
            birinciTasiyiciIteratoru3++;
        }
        int sayac = 0;
        std::cout << "Second Player, Do You Want To Defend?" << std::endl;
        if (second.getInplay().size() >= 0) {
            for (int i = 0; i < second.getInplay().size(); i++) {
                if (second.getInplay()[i]->getType() == "Creature" && second.getInplay()[i]->getTap() == true) {
                    sayac++;
                }
            }
            if (sayac > 0) {
                std::cout << "1 -> Yes, Pick A Card To Defend" << std::endl;
                std::cout << "2 -> No, Get Hit Directly" << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;
            } else {
                std::cout << "2 -> No Defenders In Play, Get Hit Directly" << std::endl;
            }
        }
        int number2;
        std::cin >> number2;
        if (number2 == 1) {
            int number3;
            std::vector<std::shared_ptr<card>> ikinciOyuncuTasiyici;
            std::vector<std::shared_ptr<card>> ikinciOyuncuIkinciTasiyici;
            std::vector<std::shared_ptr<card>>::iterator ikinciOyuncuInplayIterator = second.getInplay().begin();
            std::vector<std::shared_ptr<card>>::iterator ikincioyuncuTasiyiciIteratoru = ikinciOyuncuTasiyici.begin();
            for (int i = 0; i < second.getInplay().size(); i++) {
                if (second.getInplay()[i]->getType() == "Creature" && second.getInplay()[i]->getTap() == true) {
                    ikinciOyuncuTasiyici.push_back(second.getInplay()[i]);
                    ikinciOyuncuInplayIterator = second.getInplay().erase(ikinciOyuncuInplayIterator);
                    i -= 1;
                } else { ikinciOyuncuInplayIterator++; }
            }
            std::vector<std::shared_ptr<card>>::iterator ikinciOyuncuTasiyiciIteratoru2 = ikinciOyuncuTasiyici.begin();
            for (int i = 0; i < ikinciOyuncuTasiyici.size(); i++) {
                std::cout << i + 1 << "--> ";
                ikinciOyuncuTasiyici[i]->cardInfo();
                std::cout << std::endl;
            }
            std::cout << "Enter Number Of Creature To Defend With" << std::endl;
            std::cin >> number3;
            for (int i = 0; i < number3 - 1; i++) {
                ikinciOyuncuTasiyiciIteratoru2++;
            }
            ikinciOyuncuIkinciTasiyici.push_back(*ikinciOyuncuTasiyiciIteratoru2);
            ikinciOyuncuTasiyiciIteratoru2 = ikinciOyuncuTasiyici.erase(ikinciOyuncuTasiyiciIteratoru2);
            std::vector<std::shared_ptr<card>>::iterator secondptr3 = ikinciOyuncuTasiyici.begin();
            for (int i = 0; i < ikinciOyuncuTasiyici.size(); i++) {

                second.getInplay().push_back(*secondptr3);

                secondptr3++;
            }
            std::vector<std::shared_ptr<card>>::iterator firstCreature;
            std::vector<std::shared_ptr<card>>::iterator secondCreature;
            firstCreature = ikinciTasiyici.begin();
            secondCreature = ikinciOyuncuIkinciTasiyici.begin();

            if (firstCreature[0]->getAbility() == "None" && firstCreature[0]->getAbility2() == "None" &&
                secondCreature[0]->getAbility() == "None" && secondCreature[0]->getAbility2() == "None") {
                firstCreature[0]->setIsAttackTrue();
                secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                if (secondCreature[0]->getHP() <= 0) {
                    firstCreature[0]->setIsAttackTrue();
                    secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                    second.getGraveyard().push_back(secondCreature[0]);
                    first.getInplay().push_back(firstCreature[0]);

                    std::cout << secondCreature[0]->getName() << " Is Dead" << std::endl;
                    ikinciTasiyici.clear();
                    ikinciOyuncuIkinciTasiyici.clear();
                    return;
                } else if (secondCreature[0]->getHP() > 0) {
                    firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                    if (firstCreature[0]->getHP() <= 0) {
                        firstCreature[0]->setIsAttackTrue();
                        firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                        first.getGraveyard().push_back(firstCreature[0]);
                        second.getInplay().push_back(secondCreature[0]);

                        std::cout << firstCreature[0]->getName() << " Is Dead" << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                        firstCreature[0]->setIsAttackTrue();
                        first.getInplay().push_back(firstCreature[0]);
                        second.getInplay().push_back(secondCreature[0]);

                        std::cout << "Nobody Is Dead" << std::endl;

                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    }

                }

            } else if (firstCreature[0]->getAbility() == "First Strike" &&
                       secondCreature[0]->getAbility() == "First Strike") {
                firstCreature[0]->setIsAttackTrue();
                if (firstCreature[0]->getAbility2() == "Trample" && secondCreature[0]->getAbility2() == "Trample") {
                    secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                    if (secondCreature[0]->getHP() <= 0) {
                        second.getGraveyard().push_back(secondCreature[0]);
                        first.getInplay().push_back(firstCreature[0]);

                        second.getHitByCreature(secondCreature[0]->getHP());
                        secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                        std::cout << secondCreature[0]->getName() << " Is Dead And HP Of Enemy Is "
                                  << second.getHitPoint()
                                  << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (secondCreature[0]->getHP() > 0) {
                        firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                        if (firstCreature[0]->getHP() <= 0) {
                            first.getGraveyard().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);

                            first.getHitByCreature(firstCreature[0]->getHP());
                            firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                            std::cout << firstCreature[0]->getName() << " Is Dead And HP Of Enemy Is "
                                      << first.getHitPoint() << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                            first.getInplay().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);

                            std::cout << "Nobody Is Dead" << std::endl;

                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        }

                    }
                } else if (firstCreature[0]->getAbility2() == "Trample" && secondCreature[0]->getAbility2() == "None") {
                    secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                    if (secondCreature[0]->getHP() <= 0) {

                        second.getGraveyard().push_back(secondCreature[0]);
                        first.getInplay().push_back(firstCreature[0]);
                        second.getHitByCreature(secondCreature[0]->getHP());
                        secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                        std::cout << secondCreature[0]->getName() << " Is Dead And HP Of Enemy Is "
                                  << second.getHitPoint()
                                  << std::endl;

                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (secondCreature[0]->getHP() > 0) {
                        firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                        if (firstCreature[0]->getHP() <= 0) {
                            firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                            first.getGraveyard().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);

                            std::cout << firstCreature[0]->getName() << " Is Dead" << std::endl;

                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                            first.getInplay().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);

                            std::cout << "Nobody Is Dead" << std::endl;

                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        }

                    }

                } else if (firstCreature[0]->getAbility2() == "None" && secondCreature[0]->getAbility2() == "Trample") {
                    secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                    if (secondCreature[0]->getHP() <= 0) {
                        second.getGraveyard().push_back(secondCreature[0]);
                        first.getInplay().push_back(firstCreature[0]);

                        second.getHitByCreature(secondCreature[0]->getHP());
                        secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                        std::cout << secondCreature[0]->getName() << " Is Dead And HP Of Enemy Is "
                                  << second.getHitPoint()
                                  << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (secondCreature[0]->getHP() > 0) {
                        firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                        if (firstCreature[0]->getHP() <= 0) {
                            first.getGraveyard().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);

                            first.getHitByCreature(firstCreature[0]->getHP());
                            firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                            std::cout << firstCreature[0]->getName() << " Is Dead And HP Of Enemy Is "
                                      << first.getHitPoint() << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                            first.getInplay().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);
                            std::cout << "Nobody Is Dead" << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        }
                    }
                } else {
                    secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                    if (secondCreature[0]->getHP() <= 0) {
                        secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                        second.getGraveyard().push_back(secondCreature[0]);
                        first.getInplay().push_back(firstCreature[0]);
                        std::cout << secondCreature[0]->getName() << " Is Dead" << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (secondCreature[0]->getHP() > 0) {
                        firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                        if (firstCreature[0]->getHP() <= 0) {
                            firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                            first.getGraveyard().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);
                            std::cout << firstCreature[0]->getName() << " Is Dead" << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                            first.getInplay().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);
                            std::cout << "Nobody Is Dead" << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        }
                    }
                }
            } else if (firstCreature[0]->getAbility() == "First Strike" && secondCreature[0]->getAbility() == "None") {
                firstCreature[0]->setIsAttackTrue();
                if (firstCreature[0]->getAbility2() == "Trample") {
                    secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                    if (secondCreature[0]->getHP() <= 0) {
                        second.getGraveyard().push_back(secondCreature[0]);
                        first.getInplay().push_back(firstCreature[0]);
                        second.getHitByCreature(secondCreature[0]->getHP());
                        secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                        std::cout << secondCreature[0]->getName() << " Is Dead And HP Of Enemy Is "
                                  << second.getHitPoint() << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (secondCreature[0]->getHP() > 0) {
                        firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                        if (firstCreature[0]->getHP() <= 0) {
                            firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                            first.getGraveyard().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);
                            std::cout << firstCreature[0]->getName() << " Is Dead" << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                            first.getInplay().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);
                            std::cout << "Nobody Is Dead" << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        }
                    }
                } else {
                    secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                    if (secondCreature[0]->getHP() <= 0) {
                        secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                        second.getGraveyard().push_back(secondCreature[0]);
                        first.getInplay().push_back(firstCreature[0]);
                        std::cout << secondCreature[0]->getName() << " Is Dead" << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (secondCreature[0]->getHP() > 0) {
                        firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                        if (firstCreature[0]->getHP() <= 0) {
                            firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                            first.getGraveyard().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);
                            std::cout << firstCreature[0]->getName() << " Is Dead" << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                            first.getInplay().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);
                            std::cout << "Nobody Is Dead" << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        }
                    }
                }
            } else if (firstCreature[0]->getAbility() == "None" && secondCreature[0]->getAbility() == "First Strike") {
                firstCreature[0]->setIsAttackTrue();
                if (firstCreature[0]->getAbility2() == "Trample") {
                    secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                    if (secondCreature[0]->getHP() <= 0) {
                        second.getGraveyard().push_back(secondCreature[0]);
                        first.getInplay().push_back(firstCreature[0]);
                        second.getHitByCreature(secondCreature[0]->getHP());
                        secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                        std::cout << secondCreature[0]->getName() << " Is Dead And HP Of Enemy Is "
                                  << second.getHitPoint() << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (secondCreature[0]->getHP() > 0) {
                        firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                        if (firstCreature[0]->getHP() <= 0) {
                            first.getGraveyard().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);
                            first.getHitByCreature(firstCreature[0]->getHP());
                            firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                            std::cout << firstCreature[0]->getName() << " Is Dead And HP Of Enemy Is "
                                      << first.getHitPoint() << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                            first.getInplay().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);
                            std::cout << "Nobody Is Dead" << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        }
                    }
                } else {
                    firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                    if (firstCreature[0]->getHP() <= 0) {
                        firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                        first.getGraveyard().push_back(firstCreature[0]);
                        second.getInplay().push_back(secondCreature[0]);
                        std::cout << firstCreature[0]->getName() << " Is Dead" << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (secondCreature[0]->getHP() > 0) {
                        secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                        if (secondCreature[0]->getHP() <= 0) {
                            secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                            second.getGraveyard().push_back(secondCreature[0]);
                            first.getInplay().push_back(firstCreature[0]);
                            std::cout << secondCreature[0]->getName() << " Is Dead" << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                            first.getInplay().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);
                            std::cout << "Nobody Is Dead" << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        }
                    }
                }
            } else if (firstCreature[0]->getAbility() == "Trample" && secondCreature[0]->getAbility() == "None") {
                firstCreature[0]->setIsAttackTrue();
                secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                if (secondCreature[0]->getHP() <= 0) {
                    second.getGraveyard().push_back(secondCreature[0]);
                    first.getInplay().push_back(firstCreature[0]);
                    second.getHitByCreature(secondCreature[0]->getHP());
                    secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                    std::cout << secondCreature[0]->getName() << " Is Dead And HP Of Enemy Is " << second.getHitPoint()
                              << std::endl;
                    ikinciTasiyici.clear();
                    ikinciOyuncuIkinciTasiyici.clear();
                    return;
                } else if (secondCreature[0]->getHP() > 0) {
                    firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                    if (firstCreature[0]->getHP() <= 0) {
                        firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                        first.getGraveyard().push_back(firstCreature[0]);
                        second.getInplay().push_back(secondCreature[0]);
                        std::cout << firstCreature[0]->getName() << " Is Dead" << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                        first.getInplay().push_back(firstCreature[0]);
                        second.getInplay().push_back(secondCreature[0]);
                        std::cout << "Nobody Is Dead" << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    }
                }
            } else if (firstCreature[0]->getAbility() == "Trample" && secondCreature[0]->getAbility() == "Trample") {
                firstCreature[0]->setIsAttackTrue();
                secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                if (secondCreature[0]->getHP() <= 0) {
                    second.getGraveyard().push_back(secondCreature[0]);
                    first.getInplay().push_back(firstCreature[0]);
                    second.getHitByCreature(secondCreature[0]->getHP());
                    secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                    std::cout << secondCreature[0]->getName() << " Is Dead And HP Of Enemy Is " << second.getHitPoint()<< std::endl;
                    ikinciTasiyici.clear();
                    ikinciOyuncuIkinciTasiyici.clear();
                    return;
                } else if (secondCreature[0]->getHP() > 0) {
                    firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                    if (firstCreature[0]->getHP() <= 0) {
                        first.getGraveyard().push_back(firstCreature[0]);
                        second.getInplay().push_back(secondCreature[0]);
                        first.getHitByCreature(firstCreature[0]->getHP());
                        firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                        std::cout << firstCreature[0]->getName() << " Is Dead And HP Of Enemy Is "<< first.getHitPoint() << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                        first.getInplay().push_back(firstCreature[0]);
                        second.getInplay().push_back(secondCreature[0]);
                        std::cout << "Nobody Is Dead" << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    }
                }
            } else if (firstCreature[0]->getAbility() == "Trample" &&
                       secondCreature[0]->getAbility() == "First Strike") {
                firstCreature[0]->setIsAttackTrue();
                if (secondCreature[0]->getAbility2() == "None") {
                    firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                    if (firstCreature[0]->getHP() <= 0) {
                        first.getGraveyard().push_back(firstCreature[0]);
                        second.getInplay().push_back(secondCreature[0]);
                        firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                        std::cout << firstCreature[0]->getName() << " Is Dead " << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (secondCreature[0]->getHP() > 0) {
                        secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                        if (secondCreature[0]->getHP() <= 0) {
                            second.getGraveyard().push_back(secondCreature[0]);
                            first.getInplay().push_back(firstCreature[0]);
                            second.getHitByCreature(secondCreature[0]->getHP());
                            secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                            std::cout << secondCreature[0]->getName() << " Is Dead And HP Of Enemy Is "<< second.getHitPoint() << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                            first.getInplay().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);
                            std::cout << "Nobody Is Dead" << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        }
                    }
                }
            } else if (firstCreature[0]->getAbility() == "None" && secondCreature[0]->getAbility() == "Trample") {
                firstCreature[0]->setIsAttackTrue();
                if (firstCreature[0]->getAbility2() == "None") {
                    secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                    if (secondCreature[0]->getHP() <= 0) {
                        second.getGraveyard().push_back(secondCreature[0]);
                        first.getInplay().push_back(firstCreature[0]);
                        secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                        std::cout << secondCreature[0]->getName() << " Is Dead " << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (secondCreature[0]->getHP() > 0) {
                        firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                        if (firstCreature[0]->getHP() <= 0) {
                            first.getGraveyard().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);
                            first.getHitByCreature(firstCreature[0]->getHP());
                            firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                            std::cout << firstCreature[0]->getName() << " Is Dead And HP Of Enemy Is "<< first.getHitPoint() << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                            first.getInplay().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);
                            std::cout << "Nobody Is Dead " << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        }
                    }
                } else {
                    secondCreature[0]->setHPOf(secondCreature[0]->getHP() - firstCreature[0]->getAP());
                    if (secondCreature[0]->getHP() <= 0) {
                        second.getGraveyard().push_back(secondCreature[0]);
                        first.getInplay().push_back(firstCreature[0]);
                        second.getHitByCreature(secondCreature[0]->getHP());
                        secondCreature[0]->setHPOf(secondCreature[0]->getBaseHp());
                        std::cout << secondCreature[0]->getName() << " Is Dead And HP Of Enemy Is "
                                  << second.getHitPoint() << std::endl;
                        ikinciTasiyici.clear();
                        ikinciOyuncuIkinciTasiyici.clear();
                        return;
                    } else if (secondCreature[0]->getHP() > 0) {
                        firstCreature[0]->setHPOf(firstCreature[0]->getHP() - secondCreature[0]->getAP());
                        if (firstCreature[0]->getHP() <= 0) {
                            first.getGraveyard().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);
                            first.getHitByCreature(firstCreature[0]->getHP());
                            firstCreature[0]->setHPOf(firstCreature[0]->getBaseHp());
                            std::cout << firstCreature[0]->getName() << " Is Dead And HP Of Enemy Is "
                                      << first.getHitPoint() << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        } else if (firstCreature[0]->getHP() > 0 && secondCreature[0]->getHP() > 0) {
                            first.getInplay().push_back(firstCreature[0]);
                            second.getInplay().push_back(secondCreature[0]);
                            std::cout << "Nobody Is Dead" << std::endl;
                            ikinciTasiyici.clear();
                            ikinciOyuncuIkinciTasiyici.clear();
                            return;
                        }
                    }
                }
            }
        } else if (number2 = 2) {
            second.getHitByCreature(-ikinciTasiyici[0]->getAP());
            std::cout << "Enemy Player got hit by " << ikinciTasiyici[0]->getName() << " with "
                      << ikinciTasiyici[0]->getAP() << std::endl;
            ikinciTasiyici[0]->setIsAttackTrue();
            first.getInplay().push_back(ikinciTasiyici[0]);
            ikinciTasiyici.clear();
        }
    }
}
void setBaseHp(player &p){
    for(int i=0;i<p.getInplay().size();i++){
        if(p.getInplay()[i]->getType()=="Creature"){
            p.getInplay()[i]->setHPOf(p.getInplay()[i]->getBaseHp());
        }
        else{}
    }
}
void checkIfThereIsDead(player &first,player &second){
    std::vector<std::shared_ptr<card>>::iterator ptr1=first.getInplay().begin();
    for(int i=0;i<first.getInplay().size();i++){
        if(first.getInplay()[i]->getHP()<=0 && first.getInplay()[i]->getType() =="Creature")  {
            std::cout<<first.getInplay()[i]->getName()<<"' Is Dead"<<std::endl;
            first.getGraveyard().push_back(*ptr1);
            ptr1=first.getInplay().erase(ptr1);
            i-=1;
        }
        else{ptr1++;
        }
    }
    std::vector<std::shared_ptr<card>>::iterator ptr2=second.getInplay().begin();
    for(int i=0;i<second.getInplay().size();i++){
        if(second.getInplay()[i]->getHP()<=0 && second.getInplay()[i]->getType() =="Creature"){
            std::cout<<second.getInplay()[i]->getName()<<"' Is Dead"<<std::endl;
            second.getGraveyard().push_back(*ptr2);
            ptr2=second.getInplay().erase(ptr2);
            i-=1;
        }
        else{ptr2++;
        }
    }
}