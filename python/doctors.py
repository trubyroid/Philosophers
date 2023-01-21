import threading
import time


def blast(name, screwdriver) -> None:
    screwdriver.event.wait()
    screwdriver.event.clear()
    screwdriver.next.event.wait()
    screwdriver.next.event.clear()
    time.sleep(0.3)
    print(name + ": BLAST")
    screwdriver.next.event.set()
    screwdriver.event.set()


class Doctor:
    def __init__(self, name, screwdriver) -> None:
        self.thread = threading.Thread(target=blast,
                                       args=(name, screwdriver))

    def start(self) -> None:
        self.thread.start()

    def join(self) -> None:
        self.thread.join()


class Screwdriver:
    def __init__(self) -> None:
        self.event = threading.Event()
        self.event.set()
        self.next = None

    # append new screwdriver to the end of linked list
    def append(self, new) -> None:
        end = new
        n = self
        while (n.next):
            n = n.next
        n.next = end


def main() -> None:

    # create linked list of screwdrivers
    screwdriver = Screwdriver()
    for i in range(4):
        screwdriver.append(Screwdriver())
    screwdriver.append(screwdriver)

    # create Doctors and give each one of them a screwdriver
    doctors = []
    for i in range(9, 14):
        doctors.append(Doctor("Doctor " + str(i), screwdriver))
        screwdriver = screwdriver.next

    # start blasting
    for n in range(5):
        doctors[n].start()

    # joining
    for j in doctors:
        j.join()


if __name__ == "__main__":
    main()
