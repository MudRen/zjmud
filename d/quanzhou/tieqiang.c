// Room: /d/quanzhou/tieqiang.c
inherit ROOM;
void create()
{
	set("short", "��ǹ��");
	set("long", @LONG
����ǹ�����������ʱ������ǹ�����¡�������������������
Ⱥѻ����Ϊ������������˵��ǹ�����ѻ������񽫣�����������
��������������ֳ��Խ��Խ�ࡣ���ڰ������и�С����
LONG );
	set("exits", ([
		"west" : __DIR__"jxnanmen",
		"north" : __DIR__"nanhu",
	]));
	set("item_desc", ([
	    "��������" : "һ���ƾɵİ������±ߺ����и����ص�������\n"
		ZJOBACTS2"�궴:enter dong\n",
	]));
	set("objects", ([
		__DIR__"npc/wuya": 4
	]));
	set("outdoors", "jiaxing");
	setup();
}

void init()
{
	add_action("do_enter", "enter");
	add_action("do_enter", "zuan");
}

int do_enter(string arg)
{
	object me;
	mapping fam;

	me = this_player();
	if( !arg || arg=="" ) return 0;
	if( arg=="dong" )
	{
		if( (fam = me->query("family")) && fam["family_name"] == "ؤ��" ) 
		{
			message("vision",
				me->name() + "����ؤ�����ǹ���һ�������������˽�ȥ��\n",
				environment(me), ({me}) );
			me->move("/d/gaibang/underqz");
			message("vision",
				me->name() + "�Ӷ������˽�����\n",
				environment(me), ({me}) );
			return 1;
		}
		else 
			return notify_fail("��ôС�Ķ�������ý�ȥ��\n");
	}
}

