#include <ansi.h>;
inherit "/kungfu/class/generate/chinese";

string *names = ({
	"��������","����̽��","������ʿ","���Ĵ̿�","���ĸ���","��ָ��ʹ","ָ��ʹ","����",
});

void create()
{
	string *fams;

	set_name("������ʿ", ({"xixia wushi",}));
	set("gender", "����");
	set("age", 35);
	set("attitude", "peaceful");

	setup();
	fams = keys(init_family);
	setup_family(fams[random(sizeof(fams))]);
}

int accept_fight(object me)
{
	tell_object(me,"��Ȼ����ս�ͷſ��ֽţ���η��η�ŵģ�\n");
	return 0;
}

void init_data(int level)
{
	object me = this_object();
	mapping smap = me->query_skills();
	int lvl,i;
	string *skills;

	set_name(names[level-1], ({"xixia bing",}));

	//������ʿ�ĵȼ��븱��env�ȼ�����
	lvl = 100+level*50;

	skills = keys(smap);
	for(i=0;i<sizeof(skills);i++)
	{
		me->set_skill(skills[i],lvl);
	}

	//���飬��Ѫ�������˺�������ȼ�����
	me->set("combat_exp",lvl*lvl/10*lvl+10000);
	me->set_temp("apply/damage",lvl*2);
	me->set("jiali",lvl*2);
	me->set("qi",lvl*30);
	me->set("eff_qi",lvl*30);
	me->set("max_qi",lvl*30);
	me->set("jing",lvl*20);
	me->set("eff_jing",lvl*20);
	me->set("max_jing",lvl*20);
	me->set("neili",lvl*30);
	me->set("max_neili",lvl*30);
}

void die()
{
	int sllv,i,pot,exp;
	object weap,bo,me = this_object();
	object ob,obj;
	string *items,str;
	mapping give;

	//����sllv:1-8
	sllv = environment()->query("sllv");

	//���������Ʒ�����������б������ʸ������ȼ��й�
	give =  ([
		"/clone/vip/putao" : (10-sllv)*2,
	]);

	items = keys(give);
	for(i=0;i<sizeof(items);i++)
	{
		if(random(give[items[i]])==0)
		{
			obj = new(items[i]);
			obj->move(environment(this_object()));
		}
	}

	if (objectp(ob = query_last_damage_from()))
	{
		//��þ����ʵս���������ȼ��й�
		exp = ob->improve_experience(sllv*50);
		pot = ob->improve_potential(sllv*50);

		tell_object(ob, sprintf(HIG "�����"+query("name")+"�������%s��Ǳ�ܡ�%s��ʵս��ᡣ"NOR"\n",
				chinese_number(pot),chinese_number(exp)));

	}
	destruct(me);
}
