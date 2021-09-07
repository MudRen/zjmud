// room: /d/xingxiu/tianroad3.c
inherit ROOM;

void init();
int do_jump(string arg);

void create()
{
	set("short", "��ɽɽ·");
	set("long", @LONG
��������ɽ��´��ɽ���ɽ�ϴ����������ɪɪ������·����һƬ��ԭ��
����һ���(valley)��ס����ɽ��·��
LONG );
	set("exits", ([
	    "northup" : __DIR__"xxroad4",
	    "eastdown" : __DIR__"xxh1",
	]));
	set("item_desc", ([
		"�����" : "������ɶ����֪���ܲ�����(jump)��ȥ��\n"
		ZJOBACTS2"����ȥ:jump valley\n",
	]) );
	set("objects", ([
		"/kungfu/class/xingxiu/azi" : 1
	]));
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
		if (me->query_temp("marks/��") ) {
			message("vision", me->name() + 
			  "�͵�һ�����������µ�������һ����˻Խ�������\n",
			   environment(me), ({me}) );
			write("���͵�һ�����������µ�������һ����˻Խ�������\n");
			me->move("/d/xingxiu/tianroad4");
			message("vision", "ֻ����������һ����˻��" + 
				me->name() +  "������Ƕ��������˹��������Ƶ�������\n̴Ϫ�����¹���\n",
			environment(me), ({me}) );
			write("ֻ����������һ����˻���������Ƕ��������˹��������ǿ���ˡ����ֵô����Ϲ���������\n");
			me->set_temp("marks/��", 0);
			return 1;
		}
		else {
			write("�������ԣ���������Ǳ߱���߸ߣ�����������������ȥ�ġ�\n");
			return 1;
		}
	}
}
