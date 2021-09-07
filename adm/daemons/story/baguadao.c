// story:baguadao �Ͻ���Ե�

#include <ansi.h>

static string char_id;
static string char_name;
static string family_name;

int give_gift();
object select_character();

static mixed *story = ({
	"��һ����Ц�������̽��������˴�ʱ�㻹�����־��ܰɣ���",
	"�̽���������ĳ�������ԩ�޳𣬽��տ����ƾ���Ϊ�Σ���",
	"��һ���������һ��������ʮ�������������ֺ�����ʲô�������ɣ���",
	"�̽���ֻ���Է�����һ�������������������ӣ���",
	"�����ꡪ��",
	"ֻ��һ�������ɲ����˺�����",
	"��һ����ĿԲ�ɣ�����������˭��Ϊ�β��ִ��£���",
	"�̽�������˫�ۣ�ֻ��һ�����ָ���������һ����������ɫ���š�",
	"����̸̸�ĵ��������¼�ʤһ��α��ַ�Ҫ�Ͼ�ɱ������",
	"��һ��������Ƿ���˷Ｘʮ������������˳��ܲ�������",
	"���˵��������˷��������ѣ���",
	"��һ���������ǣ���Ҳ�����ĳ��ˡ���",
	"������Цһ��������ԭ���������������˷�����̽�������ͷ�������Լ�����ͷ����",
	"�����ֽ��ŵ�������Ȼ��ˣ��Ҳ����ֺ��ˣ���",
	"��һ����ŭ�������ޣ��Һ�һ���������ֱ�������֮�ˣ���",
	"��������ĵ�����ԭ��������˳ơ��ɶ��������ĺ�һ������",
	"��һ�������������£���",
	"��������Цһ��������������ƽ��޵ľ���������Щ��ν�Ĵ����������ҹܶ��ˡ���",
	"��һ��ŭ�����γ������䵥�����ȵ������ã��Ҿ������ĸ��У����аɣ���",
	"���˺���һ��������һչ��������ȥ��",
	"Ǻ��",
	"�꣡",
	"~������~",
	"~~~����~~~",
	"��������",
	"���˵��������ڸ��»���ʲô��˵����",
	"ֻ����һ������Ѫ�����ϣ����ŵ��ϵ�������ָ��һ�ź����ǵ�ͨ�죬����˵��������",
	"��һ��ҡ��ҡͷ����Ц��������ĳֻ�ý��ղ�֪���������죬�������ˡ����֡���",
	"����Ҳ����ǣ������ĵ�������Ȼ��ˣ���ô�������ɡ���",
	"��������",
	"�̽����������ʶ������մ���������֮������ĳ�������Իر�����",
	"���˵������ߣ�����ʲô������Ҳ���ҵ��������������������ö��ѣ�Ҳ��л�ҡ���",
	"���˶���һ�٣����ŵ�����������Ҳ�޷���$F$N�������¡���",
	"�̽������������Ͻ���Ե��������̼��洫�ؾ����������������ҵ��������˿��Բ���һ������",
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
			      $1->query_skill("zijinbagua-dao", 1) < 1 &&
			      $1->query_skill("blade", 1) > 120 &&
			      $1->query_skill("sword", 1) > 100 &&
			      $1->query("family/family_name") &&
			      $1->query("family/family_name") != "�������" &&
			      $1->query("born_family") != "�������" &&
			      $1->query("shen") < 0 &&
			      ! wizardp($1) &&
			      ! $1->query("story/baguadao") :));
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

	if (ob->query_skill("zijinbagua-dao", 1) < 50)
		ob->set_skill("zijinbagua-dao", 50);

	ob->set("story/baguadao", 1);
	tell_object(ob, HIC "����̽�������ѧϰ�����Ͻ���Ե���"NOR"\n");
	CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + ob->name(1) +
			      "���̽�������ѧϰ�����Ͻ���Ե���");
	STORY_D->remove_story("baguadao");
	return 1;
}


