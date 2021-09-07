// challenge.c

#include <ansi.h>
#include <command.h>

inherit NPC;

object with_ob = 0;

void set_lvl(int lvl)
{
	object me = this_object();
	mapping smap = me->query_skills();
	int i;
	string *skills;

	skills = keys(smap);
	for(i=0; i<sizeof(skills); i++)
	{
		me->set_skill(skills[i],lvl);
	}
	me->set("combat_exp",lvl*lvl*lvl/10+1000000);
	me->set("jiali",lvl);
	me->set("qi",lvl*2000);
	me->set("eff_qi",lvl*2000);
	me->set("max_qi",lvl*2000);
	me->set("jing",lvl*1000);
	me->set("eff_jing",lvl*1000);
	me->set("max_jing",lvl*1000);
	me->set("neili",lvl*100);
	me->set("max_neili",lvl*200);
}

varargs int receive_damage(string type, int damage, mixed who)
{
	object me = this_object();

	if(objectp(who))
	{
		me->add("boss/"+who->query("id"),damage);
		me->add("all_recive_damage",damage);
	}

	if(me->query("qi")*2 < me->query("max_qi")&&me->query_temp(""))
	{
		message_vision("$N�ҽ�һ�����³�һ����Ѫ����������ϵ�������һЩʲô����������\n", me);
	}

	return ::receive_damage(type,damage,who);
}

void die()
{
	object ob;
	object story;
	string msg;
	int expi, poti, weiwangi, scorei;
	int i;
	string *items,*killer;
	object obj;
	mapping boss,give;

	if (! objectp(ob = query_last_damage_from()))
		return;

	if (! objectp(story = "/adm/daemons/bossd"->query_running_story()))
		return;

	story->stop_story();
	msg = query("chat_lost");
	if (! msg) msg = "���д�����ô... ��ô���ܻ�������";
	command("chat " + msg);
	CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + ob->name() + "�����" + name() + "����������ԭ���ֵ����ϡ�");

//���һ��
	expi = random(query("combat_exp") / 100) + 10;
	poti = random(200) + 50;
	weiwangi = random(query("combat_exp") / 1000) + 10;
	scorei = random(query("combat_exp") / 1000) + 10;
	if (ob->query("combat_exp")>10000000) expi /= 2;
	ob->add("combat_exp", expi);
	ob->add("potential", poti);
	ob->add("weiwang", weiwangi);
	ob->add("score", scorei);

	tell_object(ob, sprintf(HIG "������%s�㾭�顢%s��Ǳ�ܣ���������%s��������%s�㽭��������"NOR"\n",
	                        chinese_number(expi),chinese_number(poti),
	                        chinese_number(weiwangi),chinese_number(scorei)));
	set("finished", 1);


//�˺�ͳ��
	killer = keys(boss=query("boss"));
	if(give = query("die_give2"))
	{
		items = keys(give);
	}
	for(i=0; i<sizeof(killer); i++)
	{
		if(objectp(ob=find_player(killer[i])))
		{
			message_vision("$N�ۼƶ�boss���"+ boss[killer[i]] +"���˺���\n", ob);
			log_file("boss_give", sprintf("%s����boss��� %d ���˺���ID="+ob->query("id")+"��\n",ctime(time()),boss[killer[i]]));
			ob->add("weiwang",boss[killer[i]]/100);

			if (ob->query("combat_exp")<10000000)
				ob->add("combat_exp",boss[killer[i]]/10);
			else ob->add("combat_exp",boss[killer[i]]/20);

			if(give&&present(ob,environment(this_object())))
			{
				int j;
				for(j=0; j<sizeof(items); j++)
				{
					if(random(give[items[j]])==0&&random(query("all_recive_damage"))<boss[killer[i]])
					{
						obj = new(items[j]);
						obj->move(ob);
						tell_object(ob,HIM"������"+obj->query("name")+"��"NOR"\n");
						CHANNEL_D->do_channel( this_object(), "ic",ob->query("name")+"�������ҵ�"+obj->query("name")+"��");
						log_file("boss_give", sprintf("%s��"+ob->query("id")+"�õ���%s��\n",ctime(time()),obj->query("name")));
					}
				}
			}
			if (ob->query("combat_exp")<10000000)
				tell_object(ob,HIM"������"+boss[killer[i]]/10+"�㾭���"+boss[killer[i]]/100+"��������"NOR"\n");
			else tell_object(ob,HIM"������"+boss[killer[i]]/20+"�㾭���"+boss[killer[i]]/100+"��������"NOR"\n");
		}
	}
//������Ʒ
	if(give = query("die_give"))
	{
		items = keys(give);
		for(i=0; i<sizeof(items); i++)
		{
			if(random(give[items[i]])==0)
			{
				obj = new(items[i]);
				obj->move(environment(this_object()));
			}
		}
	}

	call_out("destruct", 0, this_object());
}

void win()
{
	object ob;
	object story;
	string msg;

	if (sizeof(query_enemy()))
		return;

	if (! objectp(story = "/adm/daemons/bossd"->query_running_story()))
		return;

	story->stop_story();
	command("chat* haha");
	msg = query("chat_win");
	if (! msg) msg = "��ԭ���֣�����һ����";
	command("chat " + msg);
	set("finished", 1);
	call_out("destruct", 0, this_object());
	::win();
}
