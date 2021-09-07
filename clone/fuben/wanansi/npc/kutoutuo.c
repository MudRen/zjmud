#include <ansi.h>;
inherit NPC;

int shilian();

void create()
{
	set_name("��ͷ��", ({"ku toutuo"}));
	set("gender", "����");
	set("age", 45);
	set("long","�����ǿ�ͷ�ӡ�\n");
	set("attitude", "peaceful");
 	set("no_death", 1);

	set("str", 38);
	set("int", 20);
	set("con", 20);
	set("dex", 20);
	set("max_qi", 250000);
	set("eff_qi", 250000);
	set("qi", 250000);

	set("neili", 19999);
	set("max_neili", 19999);
	
	set("combat_exp", 600000);

	set_temp("apply/damage", 666);
	set_temp("apply/armor", 300);
	set_temp("apply/speed", 300);

	set("chat_chance", 2);
	set("chat_msg", ({
		 "��ͷ��̾���������������ħ�����а�������\n",
	}));

	set("inquiry", ([
		"������" : (: shilian :),
	]));

	setup();
}

void init()
{
	set_heart_beat(1);
}

int shilian()
{
	object *t,me,env,tob;
	object slnpc,hero,slroom,*slrooms;
	mixed last,now;
	mapping fam;
	int i,baselv,k;
	now = localtime(time());
	me = this_player();

	if(me->query("last_wanan")) last = localtime(me->query("last_wanan"));
	else last = localtime(0);
	if((now[5]==last[5])&&(now[7]<=last[7])&&!me->query("wanan")){
		tell_object(me,ZJOBLONG"�㱾�������ѽ�����������������\n");
		return 1;
	}

	if (! pointerp(t = me->query_team())||sizeof(t)!=2)
	{
		tell_object(me,ZJOBLONG"���������2�˶�����ܽ��룡\n");
		return 1;
	}

	if (! me->is_team_leader())
	{
		tell_object(me,ZJOBLONG"�����öӳ����Ŵ�ҽ��ɣ�\n");
		return 1;
	}

	// �ж϶����������˵ĺϷ���
	env = environment(me);
	baselv = to_int(pow(to_float(me->query("combat_exp")*10),0.33333333));
	foreach (tob in t)
	{
		if(tob->query("last_wanan")) last = localtime(tob->query("last_wanan"));
		else last = localtime(0);
		if((now[5]==last[5])&&(now[7]<=last[7])&&!tob->query("wanan")){
			tell_object(me,ZJOBLONG"�����е�"+tob->query("name")+"�Ѿ�������������������ˣ�\n");
			return 1;
		}

		if (environment(tob) != env)
		{
			tell_object(me,ZJOBLONG"����������е��˻�û�е����ء�\n");
			return 1;
		}

		if (! living(tob))
		{
			tell_object(me,ZJOBLONG"����������л����˻��Բ����ء�\n");
			return 1;
		}

		if (tob->is_fighting())
		{
			tell_object(me,ZJOBLONG"�����������������æ�Ŵ���ء�\n");
			return 1;
		}
		k = to_int(pow(to_float(tob->query("combat_exp")*10),0.33333333));
		if(baselv < k)
			baselv = k;
	}

	slrooms = children("/clone/fuben/wanansi/wanansi");
	for (i = 0; i < sizeof(slrooms); i++) {
		if(slrooms[i]->query("owner")==me->query("id"))
			slroom = slrooms[i];
	}

	if(!slroom)
	{
		slroom = new("/clone/fuben/wanansi/wanansi");
		slroom->set("owner",me->query("id"));
		if(!me->query("wanan")){
			t->set("wanan",1);
			t->set("last_wanan",time());
		}
		slroom->set("sllv",me->query("wanan")-1);
		slroom->set("baselv",baselv);
		slroom->nextlv(1);
	}
	message_vision("$N�������������±�����\n", me);
	t->move(slroom);
	return 1;
}
