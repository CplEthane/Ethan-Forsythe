using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Timers;
using System.Diagnostics;

namespace _2DGameEngine
{
    public partial class Form1 : Form
    {
        public static bool line1;
        public static bool line2;
        public static bool line3;

        public static bool textbox_toggle;
        String[] textline = new String[3];

        string textlineCurrent01;
        string textlineCurrent02;
        string textlineCurrent03;
        string textlineWrite;
        string textlineTest;

        int stringlength;
        int stringiter;
        int lineiter;
        int lineiter2;
        private Image bm;

        public static Image heroCurrentFrame;
        public static Image heroFront1;
        public static Image heroFront2;

        public static Image heroBack1;
        public static Image heroBack2;

        public static Image heroLeft1;
        public static Image heroLeft2;

        public static Image heroRight1;
        public static Image heroRight2;



        static Point[] linePoint = new Point[3];

        static String[] merchantGreeting = new String[3];

        public static Image malenpc;
        private Image textbox;
        //public Image malenpc_front_2;
        private Thread timer;
        private delegate void Callback();
        int x = 0;
        int y = 0;
        int speed = 2;
        int scrollIter = 32;
        Stopwatch sp = new Stopwatch();
        Stopwatch textsp = new Stopwatch();
        Point heroScreenLoc = new Point();
        Point npc1ScreenLoc = new Point();

        roamingNPC Town1_NPC1Male = new roamingNPC();
        merchant Town1_Merchant = new merchant();

        Hero hero = new Hero();

        private int scrollScreenDirection = 4;

        public enum Direction
        {
            east,
            west,
            north,
            south,
            none
        };

        public enum Location
        {
            overworld,
            southhome,
            bayside,
            albakar
        }

        public Form1()
        {
            InitializeComponent();
            KeyDown += new KeyEventHandler(Form1_KeyDown);


            SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
            SetStyle(ControlStyles.ResizeRedraw, false);
            SetStyle(ControlStyles.UserPaint, true);
            SetStyle(ControlStyles.SupportsTransparentBackColor, true);

            line1 = false;
            line2 = false;
            line3 = false;

            DoubleBuffered = true;
            UpdateStyles();

            linePoint[0].X = 48;
            linePoint[0].Y = 280;

            linePoint[1].X = 48;
            linePoint[1].Y = 316;

            linePoint[2].X = 48;
            linePoint[2].Y = 352;

            //////////////////////////

            merchantGreeting[0] = "'Welcome to the item";
            merchantGreeting[1] = "store. What would you";
            merchantGreeting[2] = "like to buy?'";

            /////////////////////////////

            // Load Bitmap image
            bm = Image.FromFile("town.bmp");

            Load_Character_Bitmaps();

            Hero.facing = (int)Direction.south;
            Town1_Merchant.facingDirection = (int)Direction.east;

            heroCurrentFrame = heroFront1;
            Town1_Merchant.currentFrame = Town1_Merchant.facingRight1;
            textbox = Image.FromFile("textbox.png");

            textbox_toggle = false;

            malenpc = Image.FromFile("npcm1.png");
            //malenpc_front_2 = Image.FromFile("npcm2.png");

            heroScreenLoc.X = 8 * 32;
            heroScreenLoc.Y = 7 * 32 - 14;

            npc1ScreenLoc.X = 8 * 32;
            npc1ScreenLoc.Y = 4 * 32;


            Town1_NPC1Male.Map_X = 16;
            Town1_NPC1Male.Map_Y = 20;

            Town1_Merchant.Map_X = 10;
            Town1_Merchant.Map_Y = 18;

            Town1_Merchant.Screen_X = 2 * 32;
            Town1_Merchant.Screen_Y = 2 * 32;



            Hero.array[Town1_NPC1Male.Map_Y, Town1_NPC1Male.Map_X] = 1;

            Town1_NPC1Male.Screen_X = 8 * 32;
            Town1_NPC1Male.Screen_Y = 4 * 32;
            // initialize town

            y = 512;
            x = 256;

            textlineTest = "'Testing Text Goes Here'";
            textlineCurrent01 = textlineTest;
            stringlength = textlineTest.Length;

            //textlineWrite = textline[0];
            stringiter = 0;
            lineiter = 0;
            lineiter2 = 0;

            // Configure Timer
            timer = new Thread(AccurateTimer);
            timer.Priority = ThreadPriority.Highest;
            timer.Start();

            //textsp.Start();
        }

        private void AccurateTimer()
        {

            sp.Start();
            while (true)
            {
                // Invalidate panel every 60fps
                if (sp.ElapsedMilliseconds >= 17)
                {
                    OnUpdateUI();
                    sp.Restart();
                }
            }
        }

        private void OnUpdateUI()
        {
            Invoke(new Callback(UpdateUI), new object[] { });
        }

        private void UpdateUI()
        {
            // Only Update the area we need
            Invalidate(new Rectangle(0, 0, bm.Width, bm.Height));
        }

        public static string Truncate(string source, int length)
        {
            if (source.Length > length)
            {
                source = source.Substring(0, length);
            }
            return source;
        }


        protected override void OnPaint(PaintEventArgs e)
        {
            // Clear Background
            e.Graphics.Clear(Color.Black);

            Rectangle destRect = new Rectangle(0, 0, 512, 448);
            Rectangle srcRect = new Rectangle(x, y, 512, 448);

            e.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighSpeed;
            e.Graphics.PixelOffsetMode = System.Drawing.Drawing2D.PixelOffsetMode.HighSpeed;
            e.Graphics.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
            e.Graphics.CompositingQuality = System.Drawing.Drawing2D.CompositingQuality.HighSpeed;

            e.Graphics.DrawImage(bm, destRect, srcRect, GraphicsUnit.Pixel);
            e.Graphics.DrawImage(heroCurrentFrame, heroScreenLoc.X, heroScreenLoc.Y, 32, 46);

            // if town
            e.Graphics.DrawImage(malenpc, Town1_NPC1Male.Screen_X, Town1_NPC1Male.Screen_Y, 32, 32);
            e.Graphics.DrawImage(Town1_Merchant.currentFrame, Town1_Merchant.Screen_X, Town1_Merchant.Screen_Y, 32, 32);

            
            // textbox
            if (textbox_toggle)
            {
                e.Graphics.DrawImage(textbox, 40, 264, 416, 128);
                textsp.Start();


                //textlineCurrent = textline[0];
                //textlineCurrent = textlineTest;
                //textlineWrite = textlineCurrent;
                
                stringlength = textlineTest.Length;

                if (line1 == false)
                {
                    textlineCurrent01 = Truncate(textlineCurrent01, stringiter);
                    line1 = true;
                }
                if (line2 == false)
                {
                    textlineCurrent02 = Truncate(textlineCurrent02, stringiter);
                    line2 = true;
                }
                if (line3 == false)
                {
                    textlineCurrent03 = Truncate(textlineCurrent03, stringiter);
                    line3 = true;
                }
                

                if (stringiter <= stringlength+1 && textsp.ElapsedMilliseconds > 50 && lineiter == 0)
                {

                    textlineCurrent01 = textlineTest;
                    textlineCurrent01 = Truncate(textlineCurrent01, stringiter);
                    stringiter++;
                    textsp.Restart();
                    if(stringiter == stringlength+1)
                    {
                        lineiter++;
                        stringiter = 0;
                        textlineTest = textline[1];
                        textlineCurrent01 = textline[0];
                    }
                }
                
                else if(stringiter<=stringlength+1 && textsp.ElapsedMilliseconds > 50 && lineiter == 1)
                {
                    lineiter2 = 1;
                    textlineCurrent02 = textlineTest;
                    textlineCurrent02 = Truncate(textlineCurrent02, stringiter);
                    stringiter++;
                    textsp.Restart();
                    if (stringiter == stringlength+1)
                    {
                        lineiter++;
                        stringiter = 0;
                        textlineTest = textline[2];
                    }
                }
                else if (stringiter <= stringlength+1 && textsp.ElapsedMilliseconds > 50 && lineiter == 2)
                {
                    lineiter2 = 2;
                    textlineCurrent03 = textlineTest;
                    textlineCurrent03 = Truncate(textlineCurrent03, stringiter);
                    stringiter++;
                    textsp.Restart();
                    if (stringiter == stringlength+1)
                    {
                        lineiter++;
                        stringiter = 0;
                       
                    }
                }


                e.Graphics.DrawString(textlineCurrent01, new Font("Dragon Warrior (NES)", 12), new SolidBrush(Color.White), new Point(48, 280));

                if (lineiter2>=1)
                    e.Graphics.DrawString(textlineCurrent02, new Font("Dragon Warrior (NES)", 12), new SolidBrush(Color.White), new Point(48, 300));

                if (lineiter2>=2)
                    e.Graphics.DrawString(textlineCurrent03, new Font("Dragon Warrior (NES)", 12), new SolidBrush(Color.White), new Point(48, 320));

                /*  Just in case
                  stringlength = textlineTest.Length;
                textlineCurrent01 = Truncate(textlineCurrent01, stringiter);

                if (stringiter <= stringlength && textsp.ElapsedMilliseconds > 50)
                {

                    textlineCurrent01 = textlineTest;
                    textlineCurrent01 = Truncate(textlineCurrent01, stringiter);
                    stringiter++;
                    textsp.Restart();
                }
                
                else if(stringiter>stringlength && lineiter < 2)
                {
                    lineiter++;
                    stringiter = 0;
                    textlineCurrent01 = textline[lineiter];
                    textlineTest = textlineCurrent01;
                }
                */



            }


            if (scrollIter == 0)
            {
                if (Hero.array[Hero.Map_Y, Hero.Map_X] == 1)
                    Hero.array[Hero.Map_Y, Hero.Map_X] = 0;
                if (scrollScreenDirection == (int)Direction.east)
                {

                    Hero.Map_X++;
                }
                else if (scrollScreenDirection == (int)Direction.west)
                {
                    Hero.Map_X--;
                }
                else if (scrollScreenDirection == (int)Direction.north)
                {
                    Hero.Map_Y--;
                }
                else if (scrollScreenDirection == (int)Direction.south)
                {
                    Hero.Map_Y++;
                }

                scrollScreenDirection = (int)Direction.none;
                scrollIter = 32;
                hero.isMoving = false;

            }
            else if (scrollIter > 0 && scrollScreenDirection != (int)Direction.none)
            {

                if (scrollScreenDirection == (int)Direction.east)
                {
                    scrollIter -= speed;
                    x += speed;

                    Town1_NPC1Male.Screen_X -= speed;
                    Town1_Merchant.Screen_X -= speed;
                }
                else if (scrollScreenDirection == (int)Direction.west)
                {
                    scrollIter -= speed;
                    x -= speed;

                    Town1_NPC1Male.Screen_X += speed;
                    Town1_Merchant.Screen_X += speed;
                }
                else if (scrollScreenDirection == (int)Direction.north)
                {
                    scrollIter -= speed;
                    y -= speed;

                    Town1_NPC1Male.Screen_Y += speed;
                    Town1_Merchant.Screen_Y += speed;
                }
                else if (scrollScreenDirection == (int)Direction.south)
                {
                    scrollIter -= speed;
                    y += speed;

                    Town1_NPC1Male.Screen_Y -= speed;
                    Town1_Merchant.Screen_Y -= speed;
                }
            }
            base.OnPaint(e);

        }

        


        

        private void Form1_KeyDown(object sender, KeyEventArgs e) // main loop
        {


            if (e.KeyCode == Keys.Right && hero.isMoving == false && !textbox_toggle)
            {
                //x+=speed;
                Hero.facing = (int)Direction.east;
                if (heroCurrentFrame == heroRight2)
                {
                    // do nothing
                }
                else heroCurrentFrame = heroRight1;
                if (hero.CanMove((int)Direction.east))
                {
                    scrollScreenDirection = (int)Direction.east;
                    hero.isMoving = true;
                }
            }
            else if (e.KeyCode == Keys.Left && hero.isMoving == false && !textbox_toggle)
            {
                //x-=speed;
                Hero.facing = (int)Direction.west;
                if (heroCurrentFrame == heroLeft2)
                {
                    // do nothing
                }
                else heroCurrentFrame = heroLeft1;
                if (hero.CanMove((int)Direction.west))
                {
                    scrollScreenDirection = (int)Direction.west;
                    hero.isMoving = true;
                }
            }
            else if (e.KeyCode == Keys.Up && hero.isMoving == false && !textbox_toggle)
            {
                //y -= speed;
                Hero.facing = (int)Direction.north;
                if (heroCurrentFrame == heroBack2)
                {
                    // do nothing
                }
                else heroCurrentFrame = heroBack1;
                if (hero.CanMove((int)Direction.north))
                {
                    scrollScreenDirection = (int)Direction.north;
                    hero.isMoving = true;
                }
            }
            else if (e.KeyCode == Keys.Down && hero.isMoving == false && !textbox_toggle)
            {
                //y += speed;
                Hero.facing = (int)Direction.south;
                if (heroCurrentFrame == heroFront2)
                {
                    // do nothing
                }
                else heroCurrentFrame = heroFront1;
                if (hero.CanMove((int)Direction.south))
                {
                    scrollScreenDirection = (int)Direction.south;
                    hero.isMoving = true;
                }
            }
            else if (e.KeyCode == Keys.Space && hero.isMoving == false)
            {
                if (textbox_toggle == false)
                    textbox_toggle = true;
                else if (textbox_toggle == true)
                {
                    textbox_toggle = false;
                    stringiter = 0;
                    lineiter = 0;
                    lineiter2 = 0;
                    textlineCurrent01 = " ";
                    textlineCurrent02 = " ";
                    textlineCurrent03 = " ";
                }

                // test for NPC

                if (Town1_NPC1Male.canTalk())
                {
                    textline[0] = "'This is Southhome.'";
                    textline[1] = "*";
                    textline[2] = "*";
                    textlineCurrent01 = textline[0];
                    textlineTest = textlineCurrent01;
                    textlineCurrent02 = textline[1];
                    textlineCurrent03 = textline[2];
                }
                else if (Hero.array[Hero.Map_Y, Hero.Map_X] == 4)
                {
                    textline[0] = "'Welcome to the Item";
                    textline[1] = "Store! What would you";
                    textline[2] = "like to buy?'";
                    textlineCurrent01 = textline[0];
                    textlineTest = textlineCurrent01;
                    textlineCurrent02 = textline[1];
                    textlineCurrent03 = textline[2];
                }
                else
                {
                    textline[0] = "There's nobody there.";
                    textline[1] = "*";
                    textline[2] = "*";
                    textlineCurrent01 = textline[0];
                    textlineTest = textlineCurrent01;
                    textlineCurrent02 = textline[1];
                    textlineCurrent03 = textline[2];
                }



            }



        }

        private void Load_Character_Bitmaps()
        {
            heroFront1 = Image.FromFile("hikaru_front_01.png");
            heroFront2 = Image.FromFile("hikaru_front_02.png");

            heroBack1 = Image.FromFile("hikaru_back_01.png");
            heroBack2 = Image.FromFile("hikaru_back_02.png");

            heroLeft1 = Image.FromFile("hikaru_left_01.png");
            heroLeft2 = Image.FromFile("hikaru_left_02.png");

            heroRight1 = Image.FromFile("hikaru_right_01.png");
            heroRight2 = Image.FromFile("hikaru_right_02.png");

            Town1_Merchant.facingRight1 = Image.FromFile("merchant_right_01.png");
            Town1_Merchant.facingRight2 = Image.FromFile("merchant_right_02.png");
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            sp.Stop();
            timer.Abort();
        }


    }
}
