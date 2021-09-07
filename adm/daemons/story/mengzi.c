// story:mengzi.c

#include <ansi.h>

static string char_id;
static string char_name;

object select_character();
int    give_gift();

static mixed *story = ({
	"�󺵣��񼢡�",
	"�����糱��",
	"$N����������·�����ࡣ",
	"��ɫ�����ۼ������ཫ����",
	"ֻ��·��ҡҡ�λ��߹���һ�ˡ�",
	"$N�������һ���࣬�͵������...��",
	"��Ȼ�䷢������ͷ���ڽ���Ȼ�ƾɣ�ȴ���������롣",
	"$N���а������ɲ�Ҫ��һ������ӣ����������һ�����Ͳ���ȥ��",
	"�뵽����㽫�Ǹ���ְ������¶��ӣ�������������λ�������������������ࡣ��",
	"���˿��˿�$N���м�������һ·����Ϊ��������̼��������벻������������λ���ˡ���",
	"$N��������Ȼ�Ǹ�����ӣ����ã����á�",
	"...",
	"���˺����࣬�ͳ�һ���������õ��飬�ݸ�$N��",
	"$N��...",
	"���˵��������ɴ��࣬�����������Ȿ�������͸������ɡ���",
	"......",
	"�ۼ��������Ƕ�ȥ��$N���˷����е��飬��Ц��ֹ��",
	"���Ҵ��ֲ�ʶһ����Ҫ���������������뵽���$N��������һ�����������·��",
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

object select_character()
{
	object *obs;
	object ob;

	obs = filter_array(all_interactive(), (: ! wizardp($1) &&
						 living($1) &&
						 $1->query_skill("literate", 1) < 1 &&
						 ! $1->query("doing") :));
	if (! sizeof(obs))
		return 0;

	ob = obs[random(sizeof(obs))];
	char_id = ob->query("id");
	char_name = ob->name(1);
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
		msg = replace_string(msg, "$ID", char_id);
	}
	return msg;
}

int give_gift()
{
	STORY_D->remove_story("mengzi");
	STORY_D->give_gift("/clone/book/mengzi", 1,
			   HIM "\n��ž����һ��һ�����������ǰ��"NOR"\n");
	return 1;
}
