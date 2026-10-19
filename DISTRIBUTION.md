# Distribution and releases

The repository is both a portable Agent Plugin and a marketplace containing one plugin, `meddev-agent-skills`. All installation routes use the same `skills/` collection. There is no npm package or build step for consumers.

## Layout

- `skills/meddev-*/SKILL.md`: canonical skill content with portable frontmatter.
- `plugin.json`: portable Agent Plugins manifest for current Codex and Cursor.
- `.claude-plugin/plugin.json`: Claude Code compatibility manifest.
- `.cursor-plugin/plugin.json`: Cursor compatibility manifest.
- `.claude-plugin/marketplace.json`: Claude Code repository marketplace.
- `.agents/plugins/marketplace.json`: Codex repository marketplace.
- `.cursor-plugin/marketplace.json`: Cursor repository import catalog.
- `SKILLS.md`: generated mapping from stable domain IDs to skill names.

Skills previously lived in category directories such as `regulatory/iec-62304/`. They now live in `skills/meddev-iec-62304/`. Update external links and custom loaders accordingly. Domain IDs are unchanged; custom metadata has moved under `metadata`, with comma-separated strings for list values. The regulatory bodies of the skills are preserved.

## Validate before publishing

```bash
python3 -m pip install -r requirements-dev.txt
python3 scripts/validate_distribution.py
claude plugin validate . --strict
npx skills add . --list
```

After adding or renaming skills, regenerate `SKILLS.md` with `python3 scripts/validate_distribution.py --write-catalog`.

Test native installation against a local checkout before a release. Claude Code accepts `claude plugin marketplace add /absolute/path/to/meddev-agent-skills`, followed by `claude plugin install meddev-agent-skills@meddev-agent-skills`. Codex accepts `codex plugin marketplace add /absolute/path/to/meddev-agent-skills`, followed by `codex plugin add meddev-agent-skills@meddev-agent-skills`. Use an isolated test configuration to avoid modifying existing installations. In Cursor, copy the plugin into its documented local plugin directory and inspect Customize; then test repository import after pushing.

## Release

1. Run validation and review the changed skill descriptions.
2. Keep `version` synchronized in all three plugin manifests. Increment it for plugin releases; skill content versions remain independently tracked in `metadata.version`.
3. Commit and push the changes to the public repository's default branch. The GitHub commands in the README cannot install unpublished local changes.
4. Tag the release and include the layout/metadata migration in release notes.
5. Smoke-test the README installation routes against GitHub and a fresh agent session.

## Public directory discovery

A repository marketplace enables installation by repository URL. It does not automatically grant a listing in any official directory.

- **Claude Code:** users can add this marketplace immediately after publication. For wider discovery, follow the current official marketplace submission guidance linked from [Discover plugins](https://code.claude.com/docs/en/discover-plugins).
- **Codex / ChatGPT:** package and submit for review through the [OpenAI plugin submission workflow](https://developers.openai.com/plugins/deploy/submission). Review the current submission requirements before assembling the upload; repository installation and official directory publication are separate flows.
- **Cursor:** submit the public repository at [Cursor Marketplace publishing](https://cursor.com/marketplace/publish). Listing requires Cursor review.
- **Skills CLI:** the GitHub install route works independently of official marketplace approval. See the [Skills CLI](https://github.com/vercel-labs/skills) and [skills.sh](https://skills.sh) for its discovery ecosystem.

Do not advertise an official listing or endorsement until the corresponding submission is approved and published.
