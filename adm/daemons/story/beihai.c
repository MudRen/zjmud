// story:beihai ������˵

#include <ansi.h>

int give_gift(string name);

static mixed *story = ({
	"��ɽ��",
	"��������˸���Ƿ������������",
	"һ�˺�Ȼ���˽��������������죬��Ȼ��������Կ�׼��",
	"�������۾��ɵô��ģ�������׼��ҪǮ��",
	"���˹�����Ц�����ã��ã���ô�����㣬�����²����ꣿ",
	"������ں���ǩ��һ�����㡣",
	"��������Ŀ��š�",
	"���������������ʱӦ�����꣬һ�����֣�",
	"���˵�����Ȼ���ԣ�������Σ�",
	"���������һ�������������������ȡ���������ˣ�",
	"������Цһ����ת���ߡ�",
	"������ĬĬ���������ʰ���ң��Ӻ��������ˡ�",
	"......",
	"����������",
	"���������������ﰵ�����ۿ���ʱ��Ҫ�������Բ��ʹ��ˣ��Ҳ����꣬�����ܳ��Ʋʣ�",
	"��Ȼ�칬ּ�⵽������ʦ���꣬�����׼����ʱ��ɽ����һ�����֣�",
	"�����������������ۣ����˿ڰ�ĭ�����ڵ��ϡ�",
	"������������������з޷ޣ����д����������Ҿͽ���һ���ķ��꣬��������Ӯ��",
	"......",
	"���������꣬�ϵ������촦Ҫ��ͷ�����أ����أ����ˣ�����",
	"......",
	"��۴�ŭ����ô���������ԣ�",
	(: give_gift, "beihai" :),
	"��˵��������(king of dragon)����ʧ�𣬱����������䡣",
});

string prompt() { return HIM "���񻰴�˵��" NOR; }

void create()
{
	seteuid(getuid());
}

mixed query_story_message(int step)
{
	return step < sizeof(story) ? story[step] : 0;
}

int give_gift(string name)
{
	object ob;

	ob = new(CLASS_D("misc/") + name);
	if (! objectp(ob))
		return 0;

	NPC_D->place_npc(ob);
	if (! objectp(environment(ob)))
	{
		destruct(ob);
		return 0;
	}

	CHANNEL_D->do_channel(find_object(STORY_D), "sys",
			      ob->name() + "������" + environment(ob)->short() +
			      "(" + base_name(environment(ob)) + ")��");
	return 1;
}
