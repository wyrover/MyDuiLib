import sys
import os
import time
import logging
from watchdog.observers import Observer
from watchdog.events import LoggingEventHandler
from watchdog.events import FileSystemEventHandler
from watchdog.events import FileSystemEvent


class ldf_onRespondFile(object):
    def __init__(self,src,dst):
        self.srcPath = src
        self.dstPath = dst
    def checkFloder(self,filename):
        file = os.path.basename(filename)
        floder = os.path.dirname(filename)
        path = os.path.join(self.dstPath + floder[len(self.srcPath):]+"\\"+file)
        if not os.path.exists(path):
            os.makedirs(path)
    def copyFile(self,filename):
        file = os.path.basename(filename)
        floder = os.path.dirname(filename)
        path = os.path.join(self.dstPath + floder[len(self.srcPath):]+"\\"+file)
        open(path,"wb").write(open(filename,"rb").read())
    def removeFile(self,filename):
        path = os.path.join(self.dstPath + filename[len(self.srcPath):])
        path = os.path.join(path,os.path.basename(filename))
        os.remove(path)
    def onCreateFile(self,filename,isdir):
        print("created",filename,isdir)
        self.checkFloder(filename)
        if not isdir:
            self.copyFile(filename)
    def onModifyFile(self,filename,isdir):
        print("modified",filename,isdir)
        self.checkFloder(filename)
        pass
    def onDeleteFile(self,filename,isdir):
        print("deleted",filename,isdir)
        self.checkFloder(filename)
        pass
    def onMovedFile(self,filename,isdir):
        print("moved",filename,isdir)
        self.checkFloder(filename)
        pass
    

class ldf_FileSystemEventHandler(FileSystemEventHandler):
    """File system event handler on the file system."""
    def __init__(self,respond=None):
        FileSystemEventHandler.__init__(self)
        self._respond = respond
    def on_any_event(self,event):
        pass
    def on_created(self,event):
        if self._respond:
            self._respond.onCreateFile(event.src_path,event.is_directory)
    def on_modified(self, event):
        if self._respond:
            self._respond.onModifyFile(event.src_path,event.is_directory)
    def on_moved(self,event):
        if self._respond:
            self._respond.onMovedFile(event.src_path,event.is_directory)
    def on_deleted(self,event):
        if self._respond:
            self._respond.onDeleteFile(event.src_path,event.is_directory)


if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO,
                        format='%(asctime)s - %(message)s',
                        datefmt='%Y-%m-%d %H:%M:%S')
    path = sys.argv[1] if len(sys.argv) > 1 else '.'
    dest = sys.argv[2] if len(sys.argv) > 2 else '.'
    event_respond = ldf_onRespondFile(path,dest)
    event_handler = ldf_FileSystemEventHandler(event_respond)
    observer = Observer()
    observer.schedule(event_handler, path, recursive=True)
    observer.start()
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        observer.stop()
        print("stop...")
    observer.join()
