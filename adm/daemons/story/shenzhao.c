// story:shenzhao ��Ѫ��צ

#include <ansi.h>

static string char_id;
static string char_name;
static string family_name;

int give_gift();
object select_character();

static mixed *story = ({
	"ֻ���Ǻ��´󺺴�Ц�����������䣬�����ˣ��������������ǽ����������ӣ����������ˣ���",
	"�����ױ�����Ӧ�������ǣ�����Ϲܴ��Ը�����",
	"�Ϲܴ��������ؾ���������ٱ������˲������ٷ��ơ���",
	"һ���ױ�Ц�������Ƕ��ǹϹܴ�������࣬��ƾ�����ĸ���������ȸ��֣���",
	"��ͷ��Ȼ���˺ٺ�һЦ��˵������ƾ�������ˣ�ԭҲû��ȸ��֡���",
	"�����ź���һ���������Էɿ���ֻ��һ�˸��ֱ�����¶΢Ц��",
	"�Ϲܴ�����������ү��������참������˭����",
	"����΢Ц��������̤�����ա���ʱ�����������ı������ִ��ķ����䡣",
	"�����������䣬�������ƣ��ֱ����������ױ����ؿڣ��������죬�����߹���ϡ�",
	"�Ϲܴ����Ʋ����æ����һԾ���Ӵ���ȱ�������˳�ȥ��",
	"���˱�����ͷ������׷�ϣ�ȴ��һ����������ݣ�����������",
	"������Ʒ��ߣ������ǰ�������Ϲܴ���������һ��������Ѳ��������ģ��������ڵ��ϡ�",
	"���˱��ϰ��ߣ����Ϲܴ��Ѿ�����͸�ˣ�����໥����һЦ��",
	"���˺����������ж����Գ��棬���룺��������˭���书���֮�ߣ������������С���",
	"�����߽����գ��⿪�˻������˵�Ѩ�����ֽ������ױ���ʬ�������˺ӣ��ص����",
	"�˻������˲�ס��л����������������",
	"�����������������ʲų��ɻ������ݼ��������ճ£����ֽ��ϡ�������λӢ�۴�������",
	"����΢Ц�����������޵£��񵱡�Ӣ�ۡ����֣�����$F$N�����ɳ��ܶ�����Ц�ˡ���",
	"�½��ϵ����������书��ǿ��������������Ѫ��Ϊ�ɹ󣬽��պ͸���Я��һս�������ޱȡ���",
	"$NЦ���������ܶ����������£�����һ�����书��Ȼ�˵ã���",
	"�½���΢Ц���������������������ˣ�������Ѫ��צ�Ǽ��ұ����������������ձ�������£��������¡���",
	(: give_gift :),
});

void create()
{
	seteuid(getuid());

	if (! objectp(select_character()))
	{
		destruct(this_object());
		return;
	}
}

string prompt() { return HIR "�����ִ��š�" NOR; }

object select_character()
{
	object *obs;
	object ob;

	obs = filter_array(all_interactive(),
			   (: ultrap($1) &&
			      living($1) &&
			      $1->query_skill("ningxue-shenzhao", 1) < 1 &&
			      $1->query("family/family_name") &&
			      $1->query_dex() > 45 &&
			      $1->query("shen") > 0 &&
			      ! wizardp($1) &&
			      ! $1->query("story/shenzhao") :));
	if (! sizeof(obs))
		return 0;

	ob = obs[random(sizeof(obs))];
	char_id = ob->query("id");
	char_name = ob->name(1);
	family_name = ob->query("family/family_name");
	return ob;
}

mixed query_story_message(int step)
{
	mixed msg;

	if (step >= sizeof(story))
		return 0;

	msg = story[step];
	if (stringp(msg))
	{
		msg = replace_string(msg, "$N", char_name);
		msg = replace_string(msg, "$F", family_name);
		msg = replace_string(msg, "$ID", char_id);
	}
	return msg;
}

int give_gift()
{
	object ob;

	ob = find_player(char_id);
	if (! ob) return 1;

	if (ob->query_skill("ningxue-shenzhao", 1) < 10)
		ob->set_skill("ningxue-shenzhao", 10);

	ob->set("story/shenzhao", 1);
	tell_object(ob, HIC "��ӳ½�������ѧϰ������Ѫ��צ��"NOR"\n");
	CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + ob->name(1) +
			      "�ӳ½�������ѧϰ������Ѫ��צ��");
	STORY_D->remove_story("shenzhao");
	return 1;
}


