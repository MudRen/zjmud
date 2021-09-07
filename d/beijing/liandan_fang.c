// liandan_fang.c

#include <ansi.h>

inherit ROOM;

#define DAN_DIR	 "/d/beijing/npc/dan/"

int do_liandan(string arg);

void create()
{
	set("short", "������");
	set("long", @LONG
����Ҧ���������������ܶѷ���������ҩ�ģ�һ����ڵ�����¯(lu)����
�����룬���е�ҩζ���ò�ɢ����������һ��ɢ�����ĵ���ɫ������ʱ���
��ҩ�����Ѿ������������������ص�ɫ�ʡ�
LONG );
	//set("no_fight", 1);
	set("item_desc", ([
		"����¯��" : "һ�����ɫ�Ĵ�����¯��������ͣ������˿˿���̡�\n"
		ZJOBACTS2"����:liandan\n",
	]));


	set("exits", ([
		"south" : __DIR__"liandan_yaoshi",
	]));

	setup();
}

void init()
{
	add_action("do_liandan", "liandan"); 
}

int do_liandan(string arg)
{
	int time;

	object me = this_player();
	time = 10 + random(10);

	if (me->is_busy())
		return notify_fail("�����п�����˵�ɡ�\n");

	if ((int)me->query_temp("liandan") < 1)
		return notify_fail("����֮�أ��������š�\n");

	if ((int)me->query_temp("liandan") < 2)
		return notify_fail("ԭ�϶�û�У���ʲô����\n");

	if ((int)me->query_temp("liandan") == 3)
		return notify_fail("��ҩ�����У�������ġ�\n");

	if ((int)me->query_temp("liandan") == 4)
		return notify_fail("���Ƴɹ�����ȥ�����ɡ�\n");

	if ((int)me->query("jing") < 80 ||
	    (int)me->query("qi") < 80)
		return notify_fail("���Ѿ���ƣ�����ˡ�\n");

	message_vision(HIY "$N" HIY "��ԭ��ҩ��һһ�Ž�¯�У��������£���Ŀ������"NOR"\n", me); 
	me->set_temp("liandan", 3);
	me->start_call_out((: call_other, __FILE__, "liandan", me :), time*2);
	me->start_busy(time);
	return 1;
}

// ���ⵤ�б�
//string *SM_LIST = ({ "danS_2", "danS_3", "danS_4", "danS_5",});
string *SM_LIST = ({ 
"/d/beijing/npc/dan/danS_2",
"/d/beijing/npc/dan/danS_3",
"/d/beijing/npc/dan/danS_4",
"/d/beijing/npc/dan/danS_5",
"/clone/vip/zyao1",
"/clone/vip/zyao2",
"/clone/vip/dan_chongmai2",
"/clone/vip/dan_chongmai3",
"/clone/vip/dan_chongmai4",
});

// ��ͨ���б�
string *NORMAL_LIST = ({ "danC_4", "danD_2", "danD_3", "danD_4", });

void liandan(object me)
{
	object ob;
	int a;

	if (environment(me) != this_object())
		return;

	me->receive_damage("jing", 50 + random(30));
	me->receive_damage("qi", 50 + random(30));
	if (random(3) == 1) 
	{
		me->set_temp("liandan", 1);
		message_vision(HIR "����$N" HIR "���Ȼ��ʱ��һ��̱�"
			       "����ζ��¯�г����$N" HIR "��æ��¯ȡҩ��"
			       "�����Ū�ø���ͷ������"NOR"\n",me);
            tell_object(me,ZJFORCECMD("s")+ZJFORCECMD("s")+ZJFORCECMD("ask xiao tong about ��ҩ"));
	} else
	if (random(100) == 1)
	{
		message_vision(HIY "¯�����̽���ת������Ȼһ�����������$N"
			       HIY "��������һ������ʱ��ҩ��ζ��Ũ��$N"
			       HIY "�Ͻ������ƶ��ɵĵ���ȡ����"NOR"\n", me);
		me->set_temp("liandan", 4);
		//�ϴ��� ob = new(DAN_DIR + SM_LIST[random(sizeof(SM_LIST))]);
            //���� ob = new(random(sizeof(SM_LIST)));
            ob = new(SM_LIST[random(sizeof(SM_LIST))]);
		tell_object(me, CYN "����������Ʒ" + CYN + ob->name() + "��"NOR"\n");
		ob->move(me, 1);
            tell_object(me,ZJFORCECMD("s")+ZJFORCECMD("ask yao chun about ����"));
	} else
	{
		message_vision(HIC "¯�����̽���ת������ҩ��ζ��Ũ��$N"
			       HIC "���˵ذ����ƶ��ɵĵ���ȡ����"NOR"\n", me);
		me->set_temp("liandan", 4);
		ob = new(DAN_DIR + NORMAL_LIST[random(sizeof(NORMAL_LIST))]);
		tell_object(me, CYN "��������" + CYN + ob->name() + "��"NOR"\n");
		ob->move(me, 1);
            me->force_me("s");
            me->force_me("ask yao chun about ����");
	}
}
