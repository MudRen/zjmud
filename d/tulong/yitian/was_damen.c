#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "��������");
    set("long", @LONG
����������µĴ������ڣ�������¥���Ĳ㣬�º��һ��ʮ������
������Զ����������������ⲻʱ���ױ�������Ѳ�Ӳ쿴���䱸����ɭ�ϡ�
LONG );

    set("exits", ([
	"enter" : __DIR__"was_dayuan",
	"south" : __DIR__"road3",
    ]));

    set("objects", ([
	__DIR__"npc/bing1" : 2,
	__DIR__"npc/bing2" : 1,
    ]));

    set("no_clean_up", 0);
    setup();
}

int valid_leave(object me,string dir)
{
	object ob;

	if ( dir == "enter" && ob = present("qianfu zhang", this_object()))
	{
		ob->ccommand("tnnd"+me->query("id"));
		message_vision(CYN "$N�ȵ����ҵ����ӣ�����������Ұ��ȥ���ɣ�"NOR"\n",ob,me);
		ob->kill_ob(me);
		ob=present("guan bing 1", this_object());
		if (objectp(ob)) ob->kill_ob(me);
		ob=present("guan bing 2", this_object());
		if (objectp(ob)) ob->kill_ob(me);
		ob=present("guan bing 3", this_object());
		if (objectp(ob)) ob->kill_ob(me);
		ob=present("guan bing 4", this_object());
		if (objectp(ob)) ob->kill_ob(me);
		return notify_fail("���ű��ɹű���ס�ˡ�\n");
	}
	return 1;
}
void init()
{
	object sword, me;
	me = this_player();
	if ((objectp(sword = present("yitian sword", me))))
	{
		remove_call_out("yixiao_rob");
		call_out("yixiao_rob", 1, me, sword);
	}
}

void yixiao_rob(object me, object sword)
{
	message_vision(HIC "\nֻ��һ������ĳ�Ц��һ����Ӱ��$N" HIC
		       "ֱ�˶������㶨��һ����ԭ���������Ĵ�"
		       "�̷���֮һ�ġ�" NOR+HIB 
		       "��\n������" NOR+HIC
		       "��ΤһЦ��"NOR"\n",  me);

	if ((int)me->query_skill("parry") < 400)
	{
		message_vision(HIW "$N" HIW "ֻ���Է�������ӿ����æ����ֵ���"
			   "��ʱֻ������һ�ᣬ���콣�ѱ�ΤһЦ"
			   "���˹�ȥ��"NOR"\n", me);
		sword->move(environment(me));
		destruct(sword);
		shout(HIR "\n������������" NOR+WHT "ΤһЦ���ٺ٣���л�㽫���콣ȡ�أ����Ǻ�����ڡ�"NOR"\n" );
		write(HIR "\n������������" NOR+WHT "ΤһЦ���ٺ٣���л�㽫���콣ȡ�أ����Ǻ�����ڡ�"NOR"\n" );
	}
	else {
		message_vision(HIW "$N" HIW "���Է�������ӿ����������Ծ�𣬰�"
			   "���аγ����콣������һ�������ĺ�âֱ��Τһ"
			   "Ц��ֻ��Τ\nһЦһ���Һ���" NOR+HIR 
			   "��Ѫ" NOR+HIW 
			   "�ɽ���\n\n", me);
	}
	write(HIC "ΤһЦ��Хһ����ʩչ�����Ṧ������ƮȻ��������һ·��"
	      "�����Ѳ�������Ӱ......"NOR"\n");
}

