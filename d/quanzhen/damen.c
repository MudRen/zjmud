// damen.c ����

#include <ansi.h>
inherit ROOM;
void init();
int close_gate();
int valid_leave();
string look_gate();
int do_knock(string arg);

void create()
{
	set("short", "ȫ��̴���");
	set("long", @LONG
�����ߵ�������ɽ��ɽ����ǰ�����ȫ��̵��ܲ��������ˡ���
����ɽ�������ߵʹ������¡���Χ��ľɭɭ��������֣���ɫ���ġ�
��ǰ����ǽ���ߣ��������ݣ�����һ�����������������ߵ����ɼ
ľ��ͭ����(gate)�����Ʋ��������Ϲ���һ����(bian)����ǰ��ʯ��
�Ϲ���һ������(duilian)��
LONG
	);
	set("exits", ([
		"westdown" : __DIR__"jiaobei",
		"north" : __DIR__"jingji/enter",
	]));
	set("outdoors", "quanzhen");
	set("item_desc", ([
		"�����š�":"һ���������ߵ�"HIR"���ɼľ"HIY"��ͭ"NOR"���š�\n"
				ZJOBACTS2"����:knock gate\n",
		"�����ҡ�": HIG"
��������������������������
����		������
������ȫ���桡�š��̡�����
����		������
��������������������������"NOR"\n",
		"��������": HIY"
����һ������������������\n
�����ط����취��������Ȼ"NOR"\n"
	]) );
	set("objects",([
		__DIR__"npc/zhike" : 1,
	]));
	set("valid_startroom", 1);
	setup();
}

void init()
{
	add_action("do_knock", "knock");
}

int close_gate()
{
	object room;

	if(!( room = find_object(__DIR__"datang1")) )
		room = load_object(__DIR__"datang1");
	if(objectp(room))
	{
	delete("exits/east");
	message("vision", "ƹ��һ�����������˰Ѵ��Ź����ˡ�\n",this_object());
	if (objectp(present("qingguan", room)))
		message("vision", "֪�͵�����ǰ�Ѵ��Ź���������\n", room);
	else
		message("vision", "��ͯ��ǰ�Ѵ��Ź���������\n", room);
	}
	else message("vision", "ERROR: gate not found(close).\n", room);

	return 1;
}

int do_knock(string arg)
{
	object room;

	if (query("exits/east"))
		return notify_fail("�����Ѿ��ǿ����ˡ�\n");

	if (!arg || (arg != "gate" && arg != "east"))
		return notify_fail("��Ҫ��ʲô��\n");

	if(!( room = find_object(__DIR__"datang1")) )
		room = load_object(__DIR__"datang1");
	if(objectp(room))
	{
		set("exits/east", __DIR__"datang1");
		message_vision("$N������������ţ�ֻ��֨��һ����һλ��ͯӦ���򿪴��ţ����þ����Ŀ���������´�����$N��\n",this_player());
		message("vision", "���洫��һ������������ͯӦ����ǰ�Ѵ��ſ���\n", room);
		remove_call_out("close_gate");
		call_out("close_gate", 10);
	}

	return 1;
}

int valid_leave(object me, string dir)
{
	if (dir != "east")
	return ::valid_leave(me, dir);

	if ( (me->query("family/family_name") == "ȫ���"))
	{
		write("��ͯ�����ÿ���˵����ʦ�������ˣ������\n");
		return 1;
	}
	else if(present("chongyang ling", me))
	{
		write("��ͯ������ף������ÿ���˵����ԭ���ǹ�ͼݵ�����������\n");
		return 1;
	}
	if (me->query("shen") >= 0)
		return notify_fail("��ͯ˵������λʩ����ذգ����������Ӵ����ˡ�\n");
	else
		return notify_fail("��ͯ˵�������аħ������������򲻽��ɣ����ˣ�\n");
}

string look_gate()
{
	return "һ���������ߵ����ɼľ��ͭ���š�\n";
}
