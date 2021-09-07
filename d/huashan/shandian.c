#include <room.h>

inherit ROOM;

string *jieti_msg = ({
	HIM "����ϥ���ڵ��ϣ�ƽ�ľ��������Ž���Ϣ������ѭ��ʮ�����죬����"
	HIM "��ȫ��ͨ���裬�����������ķ�"NOR"\n"	    
	HIR "	    ת     ��      ��      ��     ��     ��"NOR"\n",
	
	HIW "��ʱֻ����һ������׹���������������ܲ���������ɫ���绮��" 
	HIW "���գ���˿�����з��ģ�����ת�����޴����������������ֳ�����" 
	HIW "�֣��ֱ���뵤����ٻ��У�ֻ�о�����Ͱٻ������˵̵�ˮ��һ" 
	HIW "�㣬�����������ˮ�Ƶ���ǰ��ȥ���������������ľ���˲�䱻�ݻ١�\n",

	HIC "����˲�䱻�ٵľ�ʹ��Щʹ����ȥ�����崫��˺���ѷε�ʹ�࣬��" 
	HIC "�����������ȫŤ���ˡ�һ�����ʱ�䶼������������о����񾭹�" 
	HIC "һ���������᳤һ�㡣"NOR"\n" ,

	HIM "��Ѩ��������������Ἧ������Ѩ�����ĵط����������������ںϣ�" 
	HIM "�����γ�̫����״������������������������������������̫�����ᣬ" 
	HIM "����̫��ͼ��ͻȻһ�����������Ҳ�����͵�����һ�£���֪����"
	HIM "������Ѩ�ɹ������������Ч����"NOR"\n",

	HIY "������ʱ�����ܵ������·�ʲôǣ���ŷ��Ŀ�ʼ��������ӿ�룬" 
	HIY "�Ծ��˵��ٶȷɿ�Ĵ�����Ѩ���ؿ�ʼ�޸��𻵵ľ�����˲���ھ���" 
	HIY "��㱼���·�о��ص���ĸ�׵Ļ���㣬���̲�סϮ���ľ��⣬����" 
	HIY "��˯����ȥ��������"NOR"\n",

	HIG "�峿������������ɢ��������Ψ�д��һƬ�ž�����������\n",
	HIR "�㷢�����ڵ���������𾪣���Ȼ�����Ѿ����˽����ɣ�����ȴ����"
	HIR "����Ϣ��ȡ֮��������֮���꣬����Ҳ���ؿ��˼���������ü������" 
	HIR "��һС����ɫ̥�ǣ���ϸ�۲�Ļ����ᷢ�����̥����ͬһ�ѵ�����" 
	HIR "����һ�㣬ɢ��������ɷ��֮���������������ӣ���������������" 
	HIR "��Ƥһ�㣬ϡ�ﻩ���ĵ��²����ϻ���Ƥ��������Щ�����Ƥ�����" 
	HIR "��������ǰ���ӵİ��ۡ�"NOR"\n",
});

int do_jieti(string arg);
int do_decide(string arg); 

void create()
{
	set("short", "��ɽ֮��");
	set("long", "�����ǻ�ɽ֮�ۣ�������Ⱥ������֮�أ���˵���ǰ�������ڴ������۽�������ͻ�Ƶ����߾��磬�����������ڴ�������ճ˷��ȥ��");
	set("exits", ([
		"south" : __DIR__"jzroad7",
	]));
	set("no_fight",1);
	set("no_fly",1);
	set("objects",([
	]));
	set("action_list",([
		"ת������":"jieti",
	]));
	setup();
}

void init()
{
	add_action("do_jieti","jieti");
}

int do_jieti(string arg)
{
	object me;
	string msg;
	me = this_player();

	msg = ZJOBLONG + HIY "ת��������һ�ֺķѴ����ľ��顢�似�������л���ѧ����ķ�ʽ��ͨ��ת��" +
		  "���ޣ����Դ�������������ʣ��������������ʡ��������ޡ��������ޡ���" +
		  "���������Ǳ������õ��ܴ����ߣ���ս���е�ɱ����Ҳ����ļ�ǿ����" +
		  "�Ƿ�ȷ���Լ�������ת�����ޣ�"NOR"\n";
	msg += ZJOBACTS2+ZJMENUF(3,3,10,30)+"ȷ��:decide\n";

	me->set_temp("attempt_jieti",1);
	tell_object(me, msg);
	add_action("do_decide","decide");
	return 1;
}

int do_decide(string arg)
{
	object me = this_player();

	if (!me->query_temp("attempt_jieti"))
		return notify_fail("�������ʲô��\n");

      //if(!wizardp(me))
	//       return notify_fail("�����У��Ժ󿪷ţ�\n");

      if(me->query("combat_exp") < 50000000)
	       return notify_fail("���鲻������ת������\n");

	if(	me->query_skill("jiuyin-shengong")< 650
		&& me->query_skill("bluesea-force")< 650
		&& me->query_skill("never-defeated")< 650
		&& me->query_skill("kuihua-mogong")< 650
	)
		return notify_fail("������Ҫ��һ����ʦ���ܴﵽ650�����ϲ���ת�����ޣ�\n");

	if((int)me->query("max_neili")< 15000)
		return notify_fail("�������û�дﵽת�����޵�������\n");
      if(me->query("magic_points") < 150000)
	       return notify_fail("������û�дﵽת�����޵�������\n");
      if(me->query_skill("martial-cognize",1) < 300 && me->query_skill("sword-cognize",1) < 300)
	       return notify_fail("�����ѧ��Ϊû�дﵽת�����޵�������\n");


	tell_object(me, HIW "���Ŀ��˼�����ã������¶����ģ�����ת�����ޣ�"NOR"\n""\n");

	me->delete_temp("attempt_jieti");
	call_out("jieti_msg", 0, me, 0);
	return 1;
}

void jieti_msg(object me, int stage, string place)
{
	string msg;

	if (stage == 5) me->revive();

	msg = HIR + jieti_msg[stage];
	tell_object(me, HIY + msg);
	if (stage < sizeof(jieti_msg) - 1)
	{
		if (stage == 4) me->unconcious();

		stage++;
		call_out("jieti_msg", 1, me, stage, place);
	} else
	{
		me->set("relife/martial_lvl",me->query_skill("martial-cognize",1));
		me->set("combat_exp",2000000);
		me->set("mud_age",1036800);//86400*3*4=18��
		CHANNEL_D->do_channel(this_object(), "rumor", HIC"��˵" + me->name(1) + "�ɹ�ת���ˣ�"NOR"\n");
		me->add("relife/zhuanshi",1);
		me->add("gain/max_qi",3000);
		me->add("gain/damage",150);//����apply/damage��
		me->add("gain/attack",150);
		me->add("gain/defense",150);
		me->add("max_neili",1000);
		me->add("max_jingli",1000);
		me->add("magic_points",10000);
		me->add("str",1);
		me->add("int",1);
		me->add("dex",1);
		me->add("con",1);
		UPDATE_D->check_user(me);
		me->save();
		log_file("zhuanshi", sprintf("%s��%s(%s) �ڻ�ɽ֮�߳ɹ�ת�����ޡ�\n", ctime(time()),me->name(1),me->query("id")) );
	}      
	return;
}
