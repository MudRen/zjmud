// story:lighting ���

#include <ansi.h>

mixed random_gift();

static mixed *story = ({
	"��ĸ����...����ɶ��",
	"�׹�����ô���㣿",
	"��ĸ��ĿԲ�������д�����˵���㱳���ﶼ�����Ҹ�Щʲô��",
	"�׹�����̬��",
	"��ĸ����...",
	"...",
	"��...",
	"����...",
	"���ƣ�������������������������������",
	(: random_gift :),
});

void create()
{
	seteuid(getuid());
}

string prompt() { return HIR "�������˻���" NOR; }

mixed query_story_message(int step)
{
	return step < sizeof(story) ? story[step] : 0;
}

mixed random_gift()
{
	object *obs;
	object ob;
	string msg;

	obs = filter_array(all_interactive(), (: ! wizardp($1) &&
						 environment($1) &&
						 environment($1)->query("outdoors") &&
						 $1->query("lightingid") &&
						 ! $1->query("doing") :));
	if (sizeof(obs) < 1) {
		obs = filter_array(all_interactive(), (: ! wizardp($1) &&
						 environment($1) &&
						 environment($1)->query("outdoors") &&
						 ! $1->query("doing") :));
	}
	if (! sizeof(obs))
		return 0;

	ob = obs[random(sizeof(obs))];
	
	if (ob->query("lightingid")) 
		ob->delete("lightingid");
	
	if (ob->query("gift/lighting") || random(5))
	{
		msg = HIR + ob->name(1) + "һ���ҽУ�����ĵ�����ȥ��" NOR;
		if (ob->query("combat_exp") < 1000000 ||
		    ob->query("qi") < 1000)
			ob->unconcious();
		else
		{
			ob->set("qi", 10);
			ob->set("eff_qi", 10);
			ob->set("jing", 1);
			ob->set("eff_jing", 1);
		}
	} else
	{
		msg = HIC "���Ǽ�" + ob->name(1) + "��������䣬��������һ�㣬�������ݡ�" NOR;
		ob->add("con", 1);
		ob->add("gift/lighting", 1);
	}
	return msg;
}

