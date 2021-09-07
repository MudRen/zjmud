// story:huanyin ����ָ��

#include <ansi.h>

static string char_id;
static string char_name;
static string family_name;

int give_gift();
object select_character();

static mixed *story = ({
	"лѷ�����������ߣ������Ҿͺ�����һ�˶�",
	"�����������̵ģ�����������Ϲ�ӣ����ҵ�ù�����ˡ�",
	"���У��������������ˣ����������������컹����ô��",
	"ΤһЦ����������������黹û���˰��������ô���ˣ�",
	"���޼ɺ���һ�����������常��������Ѫ����𣬲��ܲ������ҵ����ز��֡�",
	"�����ǺǴ�Ц���Ϸ������������ǣ�ֻ���������ж�ȡʤ���Ϸ�Ͳ��ܷ����ˡ�",
	"ΤһЦЦ������������ʹ���������ܴ�Ӯʨ������������·�����Ǿ������֡�",
	"������Цһ���������Ϸ���˼�ʮ�꣬��Ȼ��������ǰ������С���ƣ�",
	"ΤһЦ���������Ǿͱ����...",
	"ֻ��ΤһЦ����ٿ�ı�죬ֱ���˷�����˼��˫���ߵó����������һ��������������...",
	"�����������������ӣ�ΤһЦ��Ҳ���ˣ�ֻ����������������ȴ��ô�������",
	"��Ȼ·��һ��ƮȻ���������ţ�����Ϊ�Σ���",
	"ΤһЦһ��̽�����������ˣ��ȵ������ÿ�����",
	"$N�ȵ�����������˺ݶ������Ҳ����ʲô���ࡣ���漴һ������ӳ���",
	"�����ཻ��ֻ���ΤһЦ�ۻ����ң���Ѫ��ӿ����ƽƽ�ķ��˳�ȥ��һ��ˤ���ڵء�",
	"���޼ɼ�״�󾪣���æ�����������סΤһЦ��",
	"����������Ц�������Ž���������ʹ��Τ���������ҵú�ͽ���������ҿ�Ҫʧ���ˡ�",
	"���޼ɺȵ������º��ˣ�Ϊ��Ҫ���ִ��£�",
	"$N�����������������޶���������һ����������Ȼ���ұ���$N��������������������$F���ǡ�",
	"���޼ɣ�@@@@@@@",
	"......",
	"���������������ȣ��Ϸ�м�����������Ϊ������·����ָ�������¾��У�����������⣬Ҳ�ɲ���һ����",
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

string prompt() { return HIG "�����ִ��š�" NOR; }

object select_character()
{
	object *obs;
	object ob;

	obs = filter_array(all_interactive(),
			   (: ultrap($1) &&
			      living($1) &&
			      $1->query_skill("huanyin-zhi", 1) < 1 &&
			      $1->query("family/family_name") &&
			      ! wizardp($1) &&
			      ! $1->query("story/huanyin") :));
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

	if (ob->query_skill("huanyin-zhi", 1) < 10)
		ob->set_skill("huanyin-zhi", 10);

	ob->set("story/huanyin", 1);
	tell_object(ob, HIC "��ӳ�������ѧϰ���˻���ָ����"NOR"\n");
	CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + ob->name(1) +
			      "�ӳ�������ѧϰ���˻���ָ����");
	STORY_D->remove_story("huanyin");
	return 1;
}
