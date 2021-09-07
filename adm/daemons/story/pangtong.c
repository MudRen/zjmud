// story:pangtong.c

#include <ansi.h>

static string char_id;
static string char_name;

object select_character();
int give_gift();

static mixed *story = ({
	"�������Ѷ��С�",
	"���ţ���д��ʲô����",
	"С���������ʦ������д�š��伦�¡������֡�",
	"��ͳ����... ���ã��ҵ������С����������Ĳ����������ٳ��ˣ�",
	"���䣡¡¡����",
	"���Σ��ٺ٣���ͳ���Ķ��ܣ���Ϊ�����Ĵ�����������������߾��ߣ�",
	"��ͳ��κ�ӽ����أ�",
	"С���������ʦ��κ�ӽ�����ǰͷ���Ѿ������ˡ�",
	"��ͳ�����ҽ����أ�",
	"С���������ʦ�����Ͻ����ں�ͷ����û����ȡ�",
	"��ͳ�������̵ģ�����һ������������ǡ�ø����м䣡",
	"���Σ��ż���",
	"��������",
	"��ͳ�������ۣ����ڵ��ϣ������³�������Ѫ�����ˡ�",
	"......",
	"һ���ȥ��...",
	"ʮ���ȥ��...",
	"һ�����ȥ��...",
	"һǧ���ȥ��...",
	"$N������ɽ��... �ף�����ʲô��",
	"�ҶѴ���һ�ѿݹǣ��м�����б��飿",
	"$N���˳����������Ȿ���ƺ�����һ��Ĳ�����д�ġ�",
	"�������ֵǮѽ�������ҿ���....",
	"���ţ�������㣿��",
	(: give_gift :),
});

void create()
{
	seteuid(getuid());
	if (! objectp(select_character()))
	{
		STORY_D->remove_story("pangtong");
		destruct(this_object());
		return;
	}
}

string prompt() { return HIW "�����ƴ��桿" NOR; }

object select_character()
{
	object *obs;
	object ob;

	obs = filter_array(all_interactive(), (: ! wizardp($1) &&
						 living($1) &&
						 $1->query_skill("literate", 1) > 50 &&
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
	object gob;

	ob = find_player(char_id);
	if (! ob) return 1;

	STORY_D->remove_story("pangtong");

	gob = new("/clone/book/guigu");
	gob->move(ob, 1);
	CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + ob->name(1) +
			      "�������顶������㡷��");
	return 1;
}
