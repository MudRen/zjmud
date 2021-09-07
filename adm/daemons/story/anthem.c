// story:anthem ����

#include <ansi.h>

static string char_id;
static string char_name;

object select_character();
int give_gift();

static mixed *story = ({
	"�ɾ�ʯ������˵����·�������˵�ˣ��������С�",
	"$N[$ID]��...",
	"�ɾ�ʯ����˵����˵�����������ģ�",
	"$N[$ID]��...",
	"�ɾ�ʯ�����ˡ���ѽ������·",
	"��������������"
	"��ž��ž����",
	"�ɾ�ʯ������... ��ô�����ô׼��",
	"�ɾ�ʯ���������ۣ����ڵ��ϣ������³�������Ѫ�����ˡ�",
	"$N����������ӯ����ͬ־��������ˡ�",
	(: give_gift :),
});

void create()
{
	seteuid(getuid());
	if (! objectp(select_character()))
	{
		STORY_D->remove_story("anthem");
		destruct(this_object());
		return;
	}
}

string prompt() { return HIR "��������¡�" NOR; }

object select_character()
{
	object *obs;
	object ob;

	obs = filter_array(all_interactive(), (: ! wizardp($1) &&
						 living($1) &&
						 ! $1->query_skill("chinese-anthem", 1) &&
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
	object ob;

	ob = find_player(char_id);
	if (! ob) return 1;

	ob->set_skill("chinese-anthem", 200);
	STORY_D->remove_story("anthem");

	CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + ob->name(1) +
			      "���������¾���������");
	return 1;
}

