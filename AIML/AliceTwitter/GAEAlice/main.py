import cgi
import datetime
import urllib
import wsgiref.handlers

from google.appengine.ext import db
from google.appengine.api import users
from google.appengine.ext import webapp
from google.appengine.api import xmpp
from google.appengine.ext.webapp.util import run_wsgi_app

import Retrieve


class twitter(webapp.RequestHandler):
    
    def __init__(self):
        
        """
            import tweepy
            
            consumer_key = "UUbZD3yjp0kN0dqx8EWNQ"
            consumer_secret = "Hfy4VulZx6HsfpbThBBlttT7MqFXF9BXEriaNQPPJco"
            key = '381970059-hytrAbXieAt4pMlXQxnD6uYMhFQFUzUROGdFcHaC'
            secret = 'h5Nh2W1yDZWugIbLhN1v62LfA4X8wVoCQ9W7DAlP4'
            auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
            auth.set_access_token( key, secret)
            self.api = tweepy.API(auth)
            #s = self.api.update_status( "what would you like to say to @alkayyoomi?")
            #print s.id
            
        
        
            
            def friends(self):
            
            friends = self.api.friends()
            followers = self.api.followers()
           """ 
            
    
    def post(self):
        import tweepy
        
        consumer_key = "UUbZD3yjp0kN0dqx8EWNQ"
        consumer_secret = "Hfy4VulZx6HsfpbThBBlttT7MqFXF9BXEriaNQPPJco"
        key = '381970059-hytrAbXieAt4pMlXQxnD6uYMhFQFUzUROGdFcHaC'
        secret = 'h5Nh2W1yDZWugIbLhN1v62LfA4X8wVoCQ9W7DAlP4'
        auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
        auth.set_access_token( key, secret)
        self.api = tweepy.API(auth)
        message = xmpp.Message(self.request.POST)
        import time
        message.reply("let's try post this")
        self.api.update_status("My friend @%s just told me, %s"%(message.sender ,message.body))
        #time.sleep(3600)
        message.reply(" I just sent that to twitter!!")
        
        Retrieve.retrieve(auth).statistics()



application = webapp.WSGIApplication([('/_ah/xmpp/message/chat/', twitter)], debug=True)


def main():
    run_wsgi_app(application)


if __name__ == '__main__':
    main()


       


