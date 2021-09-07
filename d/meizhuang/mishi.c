// mishi.c
#include <room.h>

inherit ROOM;
int do_press();
int valid_leave();

void create()
{
       set("short","����");
       set("long", @LONG
����һ�䲻��ķ��䣬���������һ���ŵ����(shu jia)
�ͺܶ���(book)������ܵ����Կ��ż������˵ĺ��ǣ���һ��
���ع�֮�л�����һ������
LONG
     );
	set("exits", ([
		"out" : __DIR__"neitang",
	]));
	set("item_desc", ([
		"����ܡ�" :	"����ϰ��Ÿ��ָ������飬�ڶ�����Լ��ʲô�����������С�\n"
		ZJOBACTS2"����ȥ:jump shu jia\n",
		"���鼮��" :	"����һЩ��ƽ�����飬���������Լ�����\n",
	]) );
	set("objects", ([
		__DIR__"obj/tizi" : 1,
	]));

	set("no_clean_up", 0);
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

	if( !arg || arg=="" )
		return 0;
	if( arg=="shu jia")
	{
		if (me->query_temp("marks/��1") )
		{
			if (me->query_skill("dodge",1)<100)
				write("����ͼ������ܵĶ��ˣ�������������ȥ���������������򲻹���\n");
			else {
				write("������Ծ������ܶ��ˡ�\n");
				message("vision",me->name() + "һ����Ծ������ܶ��ˡ�\n",environment(me), ({me}) );
				me->move(__DIR__"dingduan");
				message("vision",me->name() + "������Ծ��������\n",environment(me), ({me}) );
			}
			return 1;
		}
		else
		{
			write("����ͼ������ܵĶ��ˣ������ǲ��̫Զ�ˣ��Ҹ���������Ӧ�ò���ˡ�\n");
			return 1;
		}
	}
}

int valid_leave(object me, string dir)
{
	me->delete_temp("marks/��1");
	return ::valid_leave(me, dir);
}

