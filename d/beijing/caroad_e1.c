#include <room.h>
inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
���ֵĶ�����������Ͻ��ǵĽ�ͨҪ������������ʯ���������ͷ���죬
·���и���������ֻ������������̽ͷ���ֵ������˲��ϣ�������ʢ��
�����Զ��������������ԶԶ����������һ�¶¸ߴ��ʵ�Ĺų�ǽ��������
�����찲�Ź㳡�ˡ������Ǿ�����Ϊ�������ֵ���������֡�
LONG );
       set("exits", ([
		"east" : __DIR__"caroad_e2",
		"west" : __DIR__"cagc_e",
		"north" : __DIR__"wang_1",
	]));
	set("objects", ([
		__DIR__"npc/girl4" : 1,
		__DIR__"npc/jumin1" : 1,
	]));
	set("item_desc", ([
		"��������" : "�ں����Ĺ�������֪���ж��\n"
		ZJOBACTS2"�궴:enter dong\n",
	]));
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
	   if( (fam = me->query("family")) && fam["family_name"] == "ؤ��")
	   {
	       message("vision",
			me->name() + "����ؤ�����ǹ���һ���������������˽�ȥ��",
			environment(me), ({me}) );
	       me->move("/d/gaibang/underbj");
	       message("vision",
			me->name() + "�Ӷ������˽�����\n",
			environment(me), ({me}) );
			return 1;
	   }
	   else  return notify_fail("��ôС�Ķ�������ý�ȥ��\n");
       }
}


