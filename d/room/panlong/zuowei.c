// zuowei.c ������

//** inherit PRIVATE_ROOM;
inherit ROOM;				   /* EXAMPLE */

void create()
{
//**    object ob;

	set("short", "������");	     /* EXAMPLE */
//**    set("short", "ROOM_NAME������");
	set("long", @LONG
�����������ᣬ�ǿ������ŵļҶ����ڵĵط�����Ȼ�����ǿտ�
������û��һ���ˡ�
LONG );

	set("default_long", "�����������ᣬ�ǿ���ROOM_NAME���ŵļҶ���" /* EXAMPLE */
			    "�ڵĵط���");			      /* EXAMPLE */
									/* EXAMPLE */

	set("exits", ([
		"west"   : __DIR__"qianting",
	]));

//**    set("objects", ([
//**	    "/d/room/roomnpc/shouwei" : 2,
//**    ]));

	set("no_sleep_room", 1);
	setup();

//**    ob = present("shou wei", this_object());
//**    ob->set("coagents", ({
//**	    ([ "startroom" : __DIR__"zuowei",
//**	       "id"	: "shou wei 1" ]),
//**	    ([ "startroom" : __DIR__"zuowei",
//**	       "id"	: "shou wei 2" ]),
//**	    ([ "startroom" : __DIR__"youwei",
//**	       "id"	: "shou wei 2" ]),
//**	    ([ "startroom" : __DIR__"youwei",
//**	       "id"	: "shou wei 1" ]),
//**    }));

//**    ob = present("shou wei 2", this_object());
//**    ob->set("coagents", ({
//**	    ([ "startroom" : __DIR__"zuowei",
//**	       "id"	: "shou wei 1" ]),
//**	    ([ "startroom" : __DIR__"zuowei",
//**	       "id"	: "shou wei 2" ]),
//**	    ([ "startroom" : __DIR__"youwei",
//**	       "id"	: "shou wei 2" ]),
//**	    ([ "startroom" : __DIR__"youwei",
//**	       "id"	: "shou wei 1" ]),
//**    }));

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}
