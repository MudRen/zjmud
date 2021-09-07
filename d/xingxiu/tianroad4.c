// room: /d/xingxiu/tianroad4.c
inherit ROOM;

void init();
int do_jump(string arg);

void create()
{
	set("short", "��ɽɽ·");
	set("long", @LONG
��������ɽ��´��ɽ���ɽ�ϴ����������ɪɪ������·����һƬ��Ҷ
�֡�ʯ����ʢ����һ���׵���ɽѩ����һ����ҩ�����ڲ�ҩ������һ����
��(valley)��ס����ɽ��·��
LONG );
	set("exits", ([
	    "westup" : __DIR__"tianroad5"
	]));
	set("objects", ([
		__DIR__"npc/caiyaoren"  : 1,
		__DIR__"obj/xuelian" : 1
	]));

	set("item_desc", ([
		"�����" : "������ɶ����֪���ܲ�����(jump)��ȥ��\n"
		ZJOBACTS2"����ȥ:jump valley\n",
	]) );
	set("outdoors", "xingxiu");

	setup();
}

void init()
{
	add_action("do_jump", "jump");
}

int do_jump(string arg)
{
	object me;
	me = this_player();

	if( !arg || arg=="" ) return 0;
	if( arg=="valley" ) {
	       message("vision", me->name() + 
			  "һ������˫�������������\n",
	       environment(me), ({me}) );
	       me->move("/d/xingxiu/tianroad3");
	       message("vision", me->name() + 
			  "�����������������\n",
	       environment(me), ({me}) );
	       return 1;
       }
}
