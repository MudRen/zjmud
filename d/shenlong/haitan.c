// haitan.c

#include <ansi.h>

inherit ROOM;

void home(object ob);

void create()
{
	set("short", "��̲");
	set("long", @LONG
��������������ˡ��ϱ���һ���޼ʵĴ󺣣���������һƬ��ľ
�֡����ϵĿ����ƺ���������, ��ʪ�ĺ����д���һ���ȳ����ּ���
��һ�����صĻ��㣬������ʮ�ֹ��졣���߲���һ�Ҵ�(chuan)��
LONG );

	set("item_desc", ([
		"���󴬡�" : "����������������ϵ�Ĵ󴬡����ϵĿ��˻����ֻҪ�ϴ�(enter)�Ϳ��Ի���ԭ��\n"
		ZJOBACTS2"�ϴ�:enter chuan\n",
	]));
	set("exits",([
		"north" :__DIR__"lin1",
	]));
	set("outdoors", "shenlong");
	setup();
}

void init()
{
	add_action("do_enter", "enter");
}

int do_enter ( string arg )
{
	object ob;
	string dir;

	ob = this_player();
	if (arg != "chuan")
	{
		tell_object(ob , "��Ҫ enter �Ķ���\n");
		return 1 ;
	}

	message_vision("����һ�������ϴ���æ����һ��������ඣ�\n", ob);
	message_vision("�������𷫣��������������С�\n", ob);
	ob ->move(__DIR__"dahai") ;
	tell_object(ob, BLU "���ں��Ϻ����˺ܾúܾ�......."NOR"\n");
	    if(ob->query("party/party_name") == "������")
	call_out("home", random(3) , ob);
	else
	call_out("home", 10 , ob);
	return 1 ;
}

void home(object ob)
{
	if (! objectp(ob) || find_object(__DIR__"dahai") != environment(ob))
		return;

	tell_object(ob, "�����ڵִ�����ԭ��һ���������С������´�����\n");
	ob->move("/d/beijing/haigang");
}
