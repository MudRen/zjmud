// lin2.c

inherit ROOM;

string* npcs = ({
	"/clone/beast/jinshe",
	"/clone/beast/qingshe",
	"/clone/beast/jinshe",
	"/clone/beast/qingshe",
	"/clone/beast/fushe",
});
 
void create()
{
	set("short", "��ľ��");
	set("long",@LONG
����һƬ��ľ�֡����˲�Զ����Ϳ��Կ��ü�ǰ��Ŀյ��ˡ�
LONG);
	set("exits", ([
		"north" : __DIR__"kongdi",
		"south" : __DIR__"lin1",
	]));
	set("objects", ([
		"/clone/beast/dushe" : 1+random(2),
		npcs[random(sizeof(npcs))] : 1,
		npcs[random(sizeof(npcs))] : 1,
		npcs[random(sizeof(npcs))] : 1,
	]) );

	set("resource/snake", ({ "/clone/beast/jinshe",
				 "/clone/beast/dushe",
				 "/clone/beast/fushe",
				 "/clone/beast/wubushe",
				 "/clone/beast/qingshe", }));

	set("outdoors", "shenlong");
	setup();
}
